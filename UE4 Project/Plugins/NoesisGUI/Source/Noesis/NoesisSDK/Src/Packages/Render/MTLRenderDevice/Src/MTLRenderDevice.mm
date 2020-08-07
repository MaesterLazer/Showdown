////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


//#undef NS_LOG_TRACE
//#define NS_LOG_TRACE(...) NS_LOG_(NS_LOG_LEVEL_TRACE, __VA_ARGS__)


#include "MTLRenderDevice.h"

#include <NsRender/RenderTarget.h>
#include <NsRender/Texture.h>
#include <NsApp/FastLZ.h>
#include <NsCore/Ptr.h>
#include <NsCore/Log.h>
#include <NsCore/HighResTimer.h>

#ifdef NS_PLATFORM_IPHONE
#include <UIKit/UIKit.h>
#endif

#include <dispatch/data.h>


using namespace Noesis;
using namespace NoesisApp;


#if __has_feature(objc_arc)
  #error ARC must be disabled for this file!
#endif

#define PREALLOCATED_DYNAMIC_PAGES 1

#define MTL_RELEASE(o) \
    NS_MACRO_BEGIN \
        [o release]; \
    NS_MACRO_END

#ifdef NS_PROFILE
    #define MTL_PUSH_DEBUG_GROUP(n) [mCommandEncoder pushDebugGroup: n]
    #define MTL_POP_DEBUG_GROUP() [mCommandEncoder popDebugGroup]
    #define MTL_NAME(o, ...) \
        NS_MACRO_BEGIN \
            o.label = [NSString stringWithFormat:__VA_ARGS__]; \
        NS_MACRO_END
#else
    #define MTL_PUSH_DEBUG_GROUP(n) NS_NOOP
    #define MTL_POP_DEBUG_GROUP() NS_NOOP
    #define MTL_NAME(o, ...) NS_NOOP
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
class MTLTexture final: public Texture
{
public:
    MTLTexture(id<MTLTexture> object_, uint32_t width_, uint32_t height_, uint32_t levels_,
        bool isInverted_): object(object_), width(width_), height(height_), levels(levels_),
        isInverted(isInverted_) {}

    ~MTLTexture()
    {
        MTL_RELEASE(object);
    }

    uint32_t GetWidth() const override { return width; }
    uint32_t GetHeight() const override { return height; }
    bool HasMipMaps() const override { return levels > 1; }
    bool IsInverted() const override { return isInverted; }

    id<MTLTexture> object;

    const uint32_t width;
    const uint32_t height;
    const uint32_t levels;
    const bool isInverted;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MTLRenderTarget final: public RenderTarget
{
public:
    MTLRenderTarget(MTLRenderPassDescriptor* passDesc_, MTLTexture* texture_, uint32_t width_,
        uint32_t height_): passDesc(passDesc_), texture(texture_), width(width_), height(height_) {}

    ~MTLRenderTarget()
    {
        MTL_RELEASE(passDesc);
    }

    Texture* GetTexture() override { return texture; }

    MTLRenderPassDescriptor* passDesc;
    Noesis::Ptr<MTLTexture> texture;

    const uint32_t width;
    const uint32_t height;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
static uint32_t Hash(MTLPixelFormat colorFormat, MTLPixelFormat stencilFormat, uint8_t sampleCount)
{
    NS_ASSERT(colorFormat < 256);
    NS_ASSERT(stencilFormat != MTLPixelFormatInvalid);
    NS_ASSERT(stencilFormat >= 250 && stencilFormat - 250 < 16);
    NS_ASSERT(sampleCount >= 1 && sampleCount - 1 < 16);

    // A pipeline hash is encoded in 32 bits. The upper 16 bits contains the information about
    // surfaces and sample count. The lower 16 bits contains the shader and render state
    //
    //       COLOR        STENCIL SAMPLES        SHADER        RENDER STATE
    //  xxxxxxxxxxxxxxxx xxxxxxxx xxxxxxxx  xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx
    //         8            4        4             8                8

    return uint32_t((colorFormat << 24) | ((stencilFormat - 250) << 20) | (sampleCount - 1) << 16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static uint32_t Hash(Shader shader, RenderState state)
{
    // In Metal only colorEnable and blendMode are part of the pipeline object
    RenderState mask = {{0, 1, 3, 0, 0, 0}};
    state.v = state.v & mask.v;
    return (uint16_t)(shader.v << 8 | state.v);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MTLRenderDevice::MTLRenderDevice(id<MTLDevice> device, bool sRGB): mDevice(device), mCommands(0),
    mCommandEncoder(0)
{
    BindAPI();
    FillCaps(sRGB);
    CreateBuffers();
    CreateStateObjects();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MTLRenderDevice::~MTLRenderDevice()
{
    MTL_RELEASE(mTextureDesc);

    for (uint32_t i = 0; i < mDynamicVB.numPages; i++)
    {
        MTL_RELEASE(mDynamicVB.pages[i].object);
    }

    for (uint32_t i = 0; i < mDynamicIB.numPages; i++)
    {
        MTL_RELEASE(mDynamicIB.pages[i].object);
    }

    for (auto& pipeline: mClearPipelines)
    {
        MTL_RELEASE(pipeline.value);
    }

    for (auto& pipeline: mPipelines)
    {
        MTL_RELEASE(pipeline.value);
    }

    for (uint32_t i = 0; i < NS_COUNTOF(mSamplers); i++)
    {
        MTL_RELEASE(mSamplers[i]);
    }

    for (uint32_t i = 0; i < NS_COUNTOF(mDepthStencilStates); i++)
    {
        MTL_RELEASE(mDepthStencilStates[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Texture> MTLRenderDevice::WrapTexture(id<MTLTexture> texture, uint32_t width,
    uint32_t height, uint32_t levels, bool isInverted)
{
    [texture retain];
    return *new MTLTexture(texture, width, height, levels, isInverted);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::PreCreatePipeline(MTLPixelFormat colorFormat, MTLPixelFormat stencilFormat,
    uint32_t sampleCount_)
{
    uint8_t sampleCount = mSampleCounts[Max(1U, Min(sampleCount_, 16U)) - 1];
    uint32_t hash = Hash(colorFormat, stencilFormat, sampleCount);
    CreatePipelines(colorFormat, stencilFormat, sampleCount, hash);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetCommandBuffer(id<MTLCommandBuffer> commands)
{
    mCommands = commands;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetOnScreenEncoder(id<MTLRenderCommandEncoder> encoder,
    MTLPixelFormat colorFormat, MTLPixelFormat stencilFormat, uint32_t sampleCount_)
{
    uint8_t sampleCount = mSampleCounts[Max(1U, Min(sampleCount_, 16U)) - 1];
    mActiveFormat = Hash(colorFormat, stencilFormat, sampleCount);
    CreatePipelines(colorFormat, stencilFormat, sampleCount, mActiveFormat);
    mCommandEncoder = encoder;
    InvalidateStateCache();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DeviceCaps& MTLRenderDevice::GetCaps() const
{
    return mCaps;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<RenderTarget> MTLRenderDevice::CreateRenderTarget(const char* label, uint32_t width,
    uint32_t height, uint32_t sampleCount_)
{
    MTLTextureUsage usage = MTLTextureUsageRenderTarget;
    MTLPixelFormat colorFormat = mCaps.linearRendering ? MTLPixelFormatBGRA8Unorm_sRGB : MTLPixelFormatBGRA8Unorm;
    MTLPixelFormat stencilFormat = MTLPixelFormatStencil8;
    uint8_t sampleCount = mSampleCounts[Max(1U, Min(sampleCount_, 16U)) - 1];

    // ColorAA
    id<MTLTexture> colorAA = nil;

    if (sampleCount > 1)
    {
        colorAA = CreateAttachment(width, height, sampleCount, colorFormat, usage);
        MTL_NAME(colorAA, @"%s_AA", label);
    }

    // Stencil
    id<MTLTexture> stencil = CreateAttachment(width, height, sampleCount, stencilFormat, usage);
    MTL_NAME(stencil, @"%s_Stencil", label);

    Noesis::Ptr<RenderTarget> rt = CreateRenderTarget(label, width, height, colorFormat, colorAA, stencil);
    MTL_RELEASE(colorAA);
    MTL_RELEASE(stencil);
    return rt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<RenderTarget> MTLRenderDevice::CloneRenderTarget(const char* label, RenderTarget* surface_)
{
    MTLRenderTarget* surface = (MTLRenderTarget*)surface_;
    NSUInteger sampleCount = surface->passDesc.colorAttachments[0].texture.sampleCount;
    MTLPixelFormat format = surface->passDesc.colorAttachments[0].texture.pixelFormat;

    id<MTLTexture> colorAA = sampleCount > 1 ? surface->passDesc.colorAttachments[0].texture : 0;
    id<MTLTexture> stencil = surface->passDesc.stencilAttachment.texture;

    return CreateRenderTarget(label, surface->width, surface->height, format, colorAA, stencil);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static MTLPixelFormat ToMTL(TextureFormat::Enum format, bool sRGB)
{
    switch (format)
    {
        case TextureFormat::RGBA8:
        {
            return sRGB? MTLPixelFormatRGBA8Unorm_sRGB : MTLPixelFormatRGBA8Unorm;
        }
        case TextureFormat::R8:
        {
            return MTLPixelFormatR8Unorm;
        }
        default:
        {
            NS_ASSERT_UNREACHABLE;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<Texture> MTLRenderDevice::CreateTexture(const char* label, uint32_t width,
    uint32_t height, uint32_t numLevels, TextureFormat::Enum format, const void** data)
{
    mTextureDesc.textureType = MTLTextureType2D;
    mTextureDesc.width = width;
    mTextureDesc.height = height;
    mTextureDesc.sampleCount = 1;
    mTextureDesc.mipmapLevelCount = numLevels;
    mTextureDesc.pixelFormat = ToMTL(format, mCaps.linearRendering);

    bool immutable = data != nullptr;

    if (@available(macOS 10.11, iOS 9, *))
    {
        mTextureDesc.usage = MTLTextureUsageShaderRead;
        if (immutable)
        {
            mTextureDesc.resourceOptions = MTLResourceStorageModePrivate;
            mTextureDesc.storageMode = MTLStorageModePrivate;
        }
        else
        {
#if defined(NS_PLATFORM_IPHONE)
            mTextureDesc.resourceOptions = MTLResourceStorageModeShared;
            mTextureDesc.storageMode = MTLStorageModeShared;
#elif defined(NS_PLATFORM_OSX)
            mTextureDesc.resourceOptions = MTLResourceStorageModeManaged | MTLResourceCPUCacheModeWriteCombined;
            mTextureDesc.storageMode = MTLStorageModeManaged;
#endif
        }
    }

    id<MTLTexture> texture = [mDevice newTextureWithDescriptor:mTextureDesc];
    MTL_NAME(texture, @"%s", label);

    Noesis::Ptr<MTLTexture> ret = *new MTLTexture(texture, width, height, numLevels, false);

    if (immutable)
    {
        if (mTextureDesc.storageMode != MTLStorageModePrivate)
        {
            for (uint32_t i = 0; i < numLevels; i++)
            {
                UpdateTexture(ret, i, 0, 0, width >> i, height >> i, data[i]);
            }
        }
        else
        {
            id<MTLCommandQueue> queue = [mCommands commandQueue];
            id<MTLCommandBuffer> commands = [queue commandBuffer];
            id<MTLBlitCommandEncoder> encoder = [commands blitCommandEncoder];

#if defined(NS_PLATFORM_IPHONE)
            mTextureDesc.resourceOptions = MTLResourceStorageModeShared;
            mTextureDesc.storageMode = MTLStorageModeShared;
#elif defined(NS_PLATFORM_OSX)
            mTextureDesc.resourceOptions = MTLResourceStorageModeManaged;
            mTextureDesc.storageMode = MTLStorageModeManaged;
#endif

            for (uint32_t i = 0; i < numLevels; i++)
            {
                uint32_t mipWidth = width >> i;
                uint32_t mipHeight = height >> i;
                NSUInteger pitch = format == TextureFormat::R8 ? mipWidth : mipWidth * 4;

                mTextureDesc.width = mipWidth;
                mTextureDesc.height = mipHeight;
                mTextureDesc.mipmapLevelCount = 1;
                id<MTLTexture> source = [mDevice newTextureWithDescriptor:mTextureDesc];

                MTLRegion region = {{0, 0}, {mipWidth, mipHeight, 1}};
                [source replaceRegion:region mipmapLevel:0 withBytes:data[i] bytesPerRow:pitch];

                [encoder copyFromTexture:source sourceSlice:0 sourceLevel:0
                    sourceOrigin:region.origin sourceSize:region.size toTexture:texture
                    destinationSlice:0 destinationLevel:0 destinationOrigin:region.origin];

                MTL_RELEASE(source);
            }

            [encoder endEncoding];
            [commands commit];
        }
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::UpdateTexture(Texture* texture_, uint32_t level, uint32_t x, uint32_t y,
    uint32_t width, uint32_t height, const void* data)
{
    MTLTexture* texture = (MTLTexture*)texture_;
    MTLRegion region = {{x, y}, {width, height, 1}};
    NSUInteger pitch = texture->object.pixelFormat == MTLPixelFormatR8Unorm ? width : width * 4;
    [texture->object replaceRegion:region mipmapLevel:level withBytes:data bytesPerRow:pitch];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::BeginRender(bool offscreen)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetRenderTarget(RenderTarget* surface_)
{
    MTLRenderTarget* surface = (MTLRenderTarget*)surface_;

    MTLPixelFormat colorFormat = surface->passDesc.colorAttachments[0].texture.pixelFormat;
    MTLPixelFormat stencilFormat = surface->passDesc.stencilAttachment.texture.pixelFormat;
    uint8_t sampleCount = (uint8_t)surface->passDesc.colorAttachments[0].texture.sampleCount;
    mActiveFormat = Hash(colorFormat, stencilFormat, sampleCount);

    CreatePipelines(colorFormat, stencilFormat, sampleCount, mActiveFormat);

    NS_ASSERT(mCommands != nullptr);
    mCommandEncoder = [mCommands renderCommandEncoderWithDescriptor:surface->passDesc];
    MTL_NAME(mCommandEncoder, @"RenderTarget");

    InvalidateStateCache();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::BeginTile(const Tile& tile, uint32_t surfaceWidth, uint32_t surfaceHeight)
{
    MTL_PUSH_DEBUG_GROUP(@"Tile");
    MTL_PUSH_DEBUG_GROUP(@"Clear");
    SetRenderPipelineState(mClearPipelines[mActiveFormat]);
    SetDepthStencilState(mDepthStencilStates[4], 0);
    SetFillMode(MTLTriangleFillModeFill);

    MTLScissorRect rect = {tile.x, surfaceHeight - (tile.y + tile.height), tile.width, tile.height};
    NS_ASSERT(mCommandEncoder != nullptr);
    [mCommandEncoder setScissorRect:rect];
    [mCommandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];
    MTL_POP_DEBUG_GROUP();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::EndTile()
{
    MTL_POP_DEBUG_GROUP();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::ResolveRenderTarget(RenderTarget* surface_, const Tile* tiles, uint32_t size)
{
    NS_ASSERT(mCommandEncoder != nullptr);

    //[mCommandEncoder textureBarrier];
    [mCommandEncoder endEncoding];
    mCommandEncoder = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::EndRender()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* MTLRenderDevice::MapVertices(uint32_t bytes)
{
    return MapBuffer(mDynamicVB, bytes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::UnmapVertices()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* MTLRenderDevice::MapIndices(uint32_t bytes)
{
    return MapBuffer(mDynamicIB, bytes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::UnmapIndices()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::DrawBatch(const Batch& batch)
{
    SetRenderState(batch);
    SetBuffers(batch);
    SetTextures(batch);

    NS_ASSERT(mCommandEncoder != nullptr);
    id<MTLBuffer> indexbuffer = mDynamicIB.currentPage->object;
    NSUInteger offset = batch.startIndex * 2 + mDynamicIB.drawPos;

    [mCommandEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:batch.numIndices
        indexType:MTLIndexTypeUInt16 indexBuffer:indexbuffer indexBufferOffset:offset];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::InvalidateStateCache()
{
    mCachedVertexBuffer = 0;
    mCachedVertexCBHash = 0;
    mCachedFragmentCBHash = 0;
    mCachedGlyphsDimensionsCBHash = 0;
    mCachedImageDimensionsCBHash = 0;
    mCachedEffectCBHash = 0;
    mCachedPipelineState = 0;
    mCachedDepthStencilState = 0;
    mCachedStencilRef = (uint32_t)-1;
    mCachedFillMode = (MTLTriangleFillMode)-1;
    memset(mCachedSamplerStates, 0, sizeof(mCachedSamplerStates));
    memset(mCachedTextures, 0, sizeof(mCachedTextures));

    NS_ASSERT(mCommandEncoder != 0);
    [mCommandEncoder setCullMode:MTLCullModeNone];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetRenderPipelineState(id<MTLRenderPipelineState> pipeline)
{
    if (mCachedPipelineState != pipeline)
    {
        [mCommandEncoder setRenderPipelineState:pipeline];
        mCachedPipelineState = pipeline;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetDepthStencilState(id<MTLDepthStencilState> state, uint32_t stencilRef)
{
    if (mCachedDepthStencilState != state)
    {
        [mCommandEncoder setDepthStencilState:state];
        mCachedDepthStencilState = state;
    }

    if (mCachedStencilRef != stencilRef)
    {
        [mCommandEncoder setStencilReferenceValue:stencilRef];
        mCachedStencilRef = stencilRef;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetFillMode(MTLTriangleFillMode fillMode)
{
    if (mCachedFillMode != fillMode)
    {
        [mCommandEncoder setTriangleFillMode:fillMode];
        mCachedFillMode = fillMode;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetRenderState(const Batch& batch)
{
    uint32_t pipelineHash = Hash(batch.shader, batch.renderState) | mActiveFormat;
    NS_ASSERT(mPipelines.Find(pipelineHash) != mPipelines.End());
    SetRenderPipelineState(mPipelines[pipelineHash]);

    NS_ASSERT(batch.renderState.f.stencilMode < NS_COUNTOF(mDepthStencilStates));
    SetDepthStencilState(mDepthStencilStates[batch.renderState.f.stencilMode], batch.stencilRef);

    SetFillMode(batch.renderState.f.wireframe ? MTLTriangleFillModeLines: MTLTriangleFillModeFill);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetBuffers(const Batch& batch)
{
    // Vertices
    NSUInteger offset = batch.vertexOffset + mDynamicVB.drawPos;
    if (mCachedVertexBuffer != mDynamicVB.currentPage->object)
    {
        [mCommandEncoder setVertexBuffer:mDynamicVB.currentPage->object offset:offset atIndex:0];
        mCachedVertexBuffer = mDynamicVB.currentPage->object;
    }
    else
    {
        [mCommandEncoder setVertexBufferOffset:offset atIndex:0];
    }

    // Projection Matrix
    if (mCachedVertexCBHash != batch.projMtxHash)
    {
        [mCommandEncoder setVertexBytes:batch.projMtx length:16 * sizeof(float) atIndex:1];
        mCachedVertexCBHash = batch.projMtxHash;
    }

    // Glyphs Texture Size
    if (batch.glyphs != 0)
    {
        MTLTexture* texture = (MTLTexture*)batch.glyphs;
        uint32_t width = texture->GetWidth();
        uint32_t height = texture->GetHeight();
        uint32_t hash = (width << 16) | height;

        if (mCachedGlyphsDimensionsCBHash != hash)
        {
            float buffer[] = { (float)width, (float)height };
            [mCommandEncoder setVertexBytes:buffer length:2 * sizeof(float) atIndex:2];
            mCachedGlyphsDimensionsCBHash = hash;
        }
    }

    // Image Texture Size
    if (batch.image != 0)
    {
        MTLTexture* texture = (MTLTexture*)batch.image;
        uint32_t width = texture->GetWidth();
        uint32_t height = texture->GetHeight();
        uint32_t hash = (width << 16) | height;

        if (mCachedImageDimensionsCBHash != hash)
        {
            float buffer[] = { 1.0f / width, 1.0f / height };
            [mCommandEncoder setFragmentBytes:buffer length:2 * sizeof(float) atIndex:1];
            mCachedImageDimensionsCBHash = hash;
        }
    }

    // Paint Constants
    if (batch.rgba != 0 || batch.radialGrad != 0 || batch.opacity != 0)
    {
        uint32_t hash = batch.rgbaHash ^ batch.radialGradHash ^ batch.opacityHash;
        if (mCachedFragmentCBHash != hash)
        {
            alignas(16) uint8_t buffer[128];
            uint32_t len = 0;

            if (batch.rgba != 0)
            {
                memcpy(buffer + len, batch.rgba, 4 * sizeof(float));
                len += 4 * sizeof(float);
            }

            if (batch.radialGrad != 0)
            {
                memcpy(buffer + len, batch.radialGrad, 8 * sizeof(float));
                len += 8 * sizeof(float);
            }

            if (batch.opacity != 0)
            {
                memcpy(buffer + len, batch.opacity, sizeof(float));
                len += sizeof(float);
            }

            NS_ASSERT(len != 0);
            NS_ASSERT(len <= sizeof(buffer));
            [mCommandEncoder setFragmentBytes:buffer length:len atIndex:0];
            mCachedFragmentCBHash = hash;
        }
    }

    // Effect constants
    if (batch.effectParamsSize != 0)
    {
        if (mCachedEffectCBHash != batch.effectParamsHash)
        {
            NSUInteger length = batch.effectParamsSize * sizeof(float);
            [mCommandEncoder setFragmentBytes:batch.effectParams length:length atIndex:2];
            mCachedEffectCBHash = batch.effectParamsHash;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetFragmentTexture(uint32_t index, id<MTLTexture> texture)
{
    NS_ASSERT(index < NS_COUNTOF(mCachedTextures));
    if (mCachedTextures[index] != texture)
    {
        [mCommandEncoder setFragmentTexture:texture atIndex:index];
        mCachedTextures[index] = texture;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetFragmentSamplerState(uint32_t index, id<MTLSamplerState> sampler)
{
    NS_ASSERT(index < NS_COUNTOF(mCachedSamplerStates));
    if (mCachedSamplerStates[index] != sampler)
    {
        [mCommandEncoder setFragmentSamplerState:sampler atIndex:index];
        mCachedSamplerStates[index] = sampler;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetTexture(uint32_t index, MTLTexture* texture, SamplerState state)
{
    NS_ASSERT(state.v < NS_COUNTOF(mSamplers));
    SetFragmentSamplerState(index, mSamplers[state.v]);
    SetFragmentTexture(index, texture->object);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::SetTextures(const Batch& batch)
{
    if (batch.pattern != 0)
    {
        SetTexture(TextureIndex::Pattern, (MTLTexture*)batch.pattern, batch.patternSampler);
    }

    if (batch.ramps != 0)
    {
        SetTexture(TextureIndex::Ramps, (MTLTexture*)batch.ramps, batch.rampsSampler);
    }

    if (batch.image != 0)
    {
        SetTexture(TextureIndex::Image, (MTLTexture*)batch.image, batch.imageSampler);
    }

    if (batch.glyphs != 0)
    {
        SetTexture(TextureIndex::Glyphs, (MTLTexture*)batch.glyphs, batch.glyphsSampler);
    }

    if (batch.shadow != 0)
    {
        SetTexture(TextureIndex::Shadow, (MTLTexture*)batch.shadow, batch.shadowSampler);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
id<MTLTexture> MTLRenderDevice::CreateAttachment(uint32_t width, uint32_t height,
    uint32_t sampleCount, MTLPixelFormat format, MTLTextureUsage usage) const
{
    mTextureDesc.textureType = sampleCount > 1 ? MTLTextureType2DMultisample : MTLTextureType2D;
    mTextureDesc.width = width;
    mTextureDesc.height = height;
    mTextureDesc.sampleCount = sampleCount;
    mTextureDesc.mipmapLevelCount = 1;
    mTextureDesc.pixelFormat = format;

    if (@available(macOS 10.11, iOS 9, *))
    {
        mTextureDesc.resourceOptions = MTLResourceStorageModePrivate;
        mTextureDesc.storageMode = MTLStorageModePrivate;
        mTextureDesc.usage = usage;
    }

#ifdef NS_PLATFORM_IPHONE
    if ([mDevice supportsFeatureSet:MTLFeatureSet_iOS_GPUFamily1_v3])
    {
        if ((usage & MTLTextureUsageShaderRead) == 0)
        {
            mTextureDesc.storageMode = MTLStorageModeMemoryless;
        }
    }
#endif

    return [mDevice newTextureWithDescriptor:mTextureDesc];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Noesis::Ptr<RenderTarget> MTLRenderDevice::CreateRenderTarget(const char* label, uint32_t width,
    uint32_t height, MTLPixelFormat format, id<MTLTexture> colorAA, id<MTLTexture> stencil) const
{
    MTLRenderPassDescriptor* passDesc = [[MTLRenderPassDescriptorClass renderPassDescriptor] retain];
    NSUInteger sampleCount = colorAA ? colorAA.sampleCount : 1;

    id<MTLTexture> color = CreateAttachment(width, height, 1, format,
        MTLTextureUsageShaderRead | (sampleCount == 1 ? MTLTextureUsageRenderTarget : 0));
    MTL_NAME(color, @"%s", label);

    if (sampleCount > 1)
    {
        NS_ASSERT(colorAA != 0);
        passDesc.colorAttachments[0].texture = colorAA;
        passDesc.colorAttachments[0].loadAction = MTLLoadActionDontCare;
        passDesc.colorAttachments[0].storeAction = MTLStoreActionMultisampleResolve;
        passDesc.colorAttachments[0].resolveTexture = color;
    }
    else
    {
        NS_ASSERT(colorAA == 0);
        passDesc.colorAttachments[0].texture = color;
        passDesc.colorAttachments[0].loadAction = MTLLoadActionDontCare;
        passDesc.colorAttachments[0].storeAction = MTLStoreActionStore;
    }

    passDesc.stencilAttachment.texture = stencil;
    passDesc.stencilAttachment.loadAction = MTLLoadActionDontCare;
    passDesc.stencilAttachment.storeAction = MTLStoreActionDontCare;

    // For combined depth-stencil formats we need to set the depth texture (even if unused)
    // For stencil-only S8 the depth format is set to Invalid
    if (stencil.pixelFormat != MTLPixelFormatStencil8)
    {
        passDesc.depthAttachment.texture = stencil;
        passDesc.depthAttachment.loadAction = MTLLoadActionDontCare;
        passDesc.depthAttachment.storeAction = MTLStoreActionDontCare;
    }

    Noesis::Ptr<MTLTexture> texture = *new MTLTexture(color, width, height, 1, false);
    return *new MTLRenderTarget(passDesc, texture, width, height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static MTLSamplerAddressMode MTLAddressModeS(SamplerState sampler)
{
    switch (sampler.f.wrapMode)
    {
        case WrapMode::ClampToEdge:
        {
            return MTLSamplerAddressModeClampToEdge;
        }
        case WrapMode::ClampToZero:
        {
            return MTLSamplerAddressModeClampToZero;
        }
        case WrapMode::Repeat:
        {
            return MTLSamplerAddressModeRepeat;
        }
        case WrapMode::MirrorU:
        {
            return MTLSamplerAddressModeMirrorRepeat;
        }
        case WrapMode::MirrorV:
        {
            return MTLSamplerAddressModeRepeat;
        }
        case WrapMode::Mirror:
        {
            return MTLSamplerAddressModeMirrorRepeat;
        }
        default:
        {
            NS_ASSERT_UNREACHABLE;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static MTLSamplerAddressMode MTLAddressModeT(SamplerState sampler)
{
    switch (sampler.f.wrapMode)
    {
        case WrapMode::ClampToEdge:
        {
            return MTLSamplerAddressModeClampToEdge;
        }
        case WrapMode::ClampToZero:
        {
            return MTLSamplerAddressModeClampToZero;
        }
        case WrapMode::Repeat:
        {
            return MTLSamplerAddressModeRepeat;
        }
        case WrapMode::MirrorU:
        {
            return MTLSamplerAddressModeRepeat;
        }
        case WrapMode::MirrorV:
        {
            return MTLSamplerAddressModeMirrorRepeat;
        }
        case WrapMode::Mirror:
        {
            return MTLSamplerAddressModeMirrorRepeat;
        }
        default:
        {
            NS_ASSERT_UNREACHABLE;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static MTLSamplerMipFilter MTLMipFilter(SamplerState sampler)
{
    switch (sampler.f.mipFilter)
    {
        case MipFilter::Disabled:
        {
            return MTLSamplerMipFilterNotMipmapped;
        }
        case MipFilter::Nearest:
        {
            return MTLSamplerMipFilterNearest;
        }
        case MipFilter::Linear:
        {
            return MTLSamplerMipFilterLinear;
        }
        default:
        {
            NS_ASSERT_UNREACHABLE;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static MTLSamplerMinMagFilter MTLMinMagFilter(SamplerState sampler)
{
    switch (sampler.f.minmagFilter)
    {
        case MinMagFilter::Nearest:
        {
            return MTLSamplerMinMagFilterNearest;
        }
        case MinMagFilter::Linear:
        {
            return MTLSamplerMinMagFilterLinear;
        }
        default:
        {
            NS_ASSERT_UNREACHABLE;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::CreateStateObjects()
{
    mTextureDesc = [[MTLTextureDescriptorClass alloc] init];

    // Sampler states
    {
        memset(mSamplers, 0, sizeof(mSamplers));
        MTLSamplerDescriptor* desc = [[MTLSamplerDescriptorClass alloc] init];

        for (uint8_t minmag = 0; minmag < MinMagFilter::Count; minmag++)
        {
            for (uint8_t mip = 0; mip < MipFilter::Count; mip++)
            {
                for (uint8_t uv = 0; uv < WrapMode::Count; uv++)
                {
                    SamplerState s = {{uv, minmag, mip}};

                    desc.mipFilter = MTLMipFilter(s);
                    desc.minFilter = MTLMinMagFilter(s);
                    desc.magFilter = MTLMinMagFilter(s);
                    desc.sAddressMode = MTLAddressModeS(s);
                    desc.tAddressMode = MTLAddressModeT(s);

                    NS_ASSERT(s.v < NS_COUNTOF(mSamplers));
                    mSamplers[s.v] = [mDevice newSamplerStateWithDescriptor:desc];
                }
            }
        }

        MTL_RELEASE(desc);
    }

    // DepthStencil states
    {
        MTLDepthStencilDescriptor* desc = [[MTLDepthStencilDescriptorClass alloc] init];

        desc.backFaceStencil = nil;
        desc.frontFaceStencil = nil;
        MTL_NAME(desc, @"Noesis::Stencil_Off");
        mDepthStencilStates[0] = [mDevice newDepthStencilStateWithDescriptor:desc];

        desc.backFaceStencil.stencilCompareFunction = MTLCompareFunctionEqual;
        desc.backFaceStencil.depthStencilPassOperation = MTLStencilOperationKeep;
        desc.frontFaceStencil = desc.backFaceStencil;
        MTL_NAME(desc, @"Noesis::Stencil_On");
        mDepthStencilStates[1] = [mDevice newDepthStencilStateWithDescriptor:desc];

        desc.backFaceStencil.stencilCompareFunction = MTLCompareFunctionEqual;
        desc.backFaceStencil.depthStencilPassOperation = MTLStencilOperationIncrementWrap;
        desc.frontFaceStencil = desc.backFaceStencil;
        MTL_NAME(desc, @"Noesis::Stencil_Incr");
        mDepthStencilStates[2] = [mDevice newDepthStencilStateWithDescriptor:desc];

        desc.backFaceStencil.stencilCompareFunction = MTLCompareFunctionEqual;
        desc.backFaceStencil.depthStencilPassOperation = MTLStencilOperationDecrementWrap;
        desc.frontFaceStencil = desc.backFaceStencil;
        MTL_NAME(desc, @"Noesis::Stencil_Decr");
        mDepthStencilStates[3] = [mDevice newDepthStencilStateWithDescriptor:desc];

        desc.backFaceStencil.stencilCompareFunction = MTLCompareFunctionAlways;
        desc.backFaceStencil.depthStencilPassOperation = MTLStencilOperationZero;
        desc.frontFaceStencil = desc.backFaceStencil;
        MTL_NAME(desc, @"Noesis::Stencil_Clear");
        mDepthStencilStates[4] = [mDevice newDepthStencilStateWithDescriptor:desc];

        MTL_RELEASE(desc);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool MTLRenderDevice::PipelinesExist(uint32_t hash) const
{
    return mClearPipelines.Find(hash) != mClearPipelines.End();
}

#if defined(NS_PLATFORM_IPHONE)
#include "Shaders.ios.h"
#elif defined(NS_PLATFORM_OSX)
#include "Shaders.macos.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::CreatePipelines(MTLPixelFormat colorFormat, MTLPixelFormat stencilFormat,
    uint8_t sampleCount, uint32_t hash)
{
    if (PipelinesExist(hash))
    {
        return;
    }

#ifdef NS_PROFILE
    uint64_t t0 = HighResTimer::Ticks();
#endif

    uint32_t shadersSize = FastLZ::DecompressBufferSize(Shaders);
    char* shaders = (char*)Alloc(shadersSize);
    FastLZ::Decompress(Shaders, sizeof(Shaders), shaders);

    NSError* error;
    dispatch_data_t data = dispatch_data_create(shaders, shadersSize, 0, ^{ ; });
    id<MTLLibrary> library = [mDevice newLibraryWithData:data error:&error];
    NS_ASSERT(error == 0);
    [(id)data autorelease];
    MTL_NAME(library, @"Noesis");

    // Vertex Functions
    id<MTLFunction> vertexFuncs[11];
    NSString* vertexNames[] =
    {
        @"Pos_VS",
        @"PosColor_VS",
        @"PosTex0_VS",
        @"PosColorCoverage_VS",
        @"PosTex0Coverage_VS",
        @"PosColorTex1_VS",
        @"PosTex0Tex1_VS",
        @"PosColorTex1Tex2_VS",
        @"PosTex0Tex1Tex2_VS",
        @"PosColorTex1_SDF_VS",
        @"PosTex0Tex1_SDF_VS"
    };

    static_assert(NS_COUNTOF(vertexFuncs) == NS_COUNTOF(vertexNames), "Size mismatch");

    for (uint32_t i = 0; i < NS_COUNTOF(vertexNames); i++)
    {
        vertexFuncs[i] = [library newFunctionWithName:vertexNames[i]];
        NS_ASSERT(vertexFuncs[i] != nil);
        MTL_NAME(vertexFuncs[i], @"%@", vertexNames[i]);
    }

    // Fragment Functions
    id<MTLFunction> fragmentFuncs[47];
    NSString* fragmentNames[] =
    {
        @"RGBA_FS",
        @"PathSolid_FS",
        @"PathLinear_FS",
        @"PathRadial_FS",
        @"PathPattern_FS",
        @"PathAASolid_FS",
        @"PathAALinear_FS",
        @"PathAARadial_FS",
        @"PathAAPattern_FS",
        @"SDFSolid_FS",
        @"SDFLinear_FS",
        @"SDFRadial_FS",
        @"SDFPattern_FS",
        @"ImageOpacitySolid_FS",
        @"ImageOpacityLinear_FS",
        @"ImageOpacityRadial_FS",
        @"ImageOpacityPattern_FS",
        @"ImageShadow35V_FS",
        @"ImageShadow63V_FS",
        @"ImageShadow127V_FS",
        @"ImageShadow35HSolid_FS",
        @"ImageShadow35HLinear_FS",
        @"ImageShadow35HRadial_FS",
        @"ImageShadow35HPattern_FS",
        @"ImageShadow63HSolid_FS",
        @"ImageShadow63HLinear_FS",
        @"ImageShadow63HRadial_FS",
        @"ImageShadow63HPattern_FS",
        @"ImageShadow127HSolid_FS",
        @"ImageShadow127HLinear_FS",
        @"ImageShadow127HRadial_FS",
        @"ImageShadow127HPattern_FS",
        @"ImageBlur35V_FS",
        @"ImageBlur63V_FS",
        @"ImageBlur127V_FS",
        @"ImageBlur35HSolid_FS",
        @"ImageBlur35HLinear_FS",
        @"ImageBlur35HRadial_FS",
        @"ImageBlur35HPattern_FS",
        @"ImageBlur63HSolid_FS",
        @"ImageBlur63HLinear_FS",
        @"ImageBlur63HRadial_FS",
        @"ImageBlur63HPattern_FS",
        @"ImageBlur127HSolid_FS",
        @"ImageBlur127HLinear_FS",
        @"ImageBlur127HRadial_FS",
        @"ImageBlur127HPattern_FS"
    };

    static_assert(NS_COUNTOF(fragmentFuncs) == NS_COUNTOF(fragmentNames), "Size mismatch");

    for (uint32_t i = 0; i < NS_COUNTOF(fragmentNames); i++)
    {
        fragmentFuncs[i] = [library newFunctionWithName:fragmentNames[i]];
        NS_ASSERT(fragmentFuncs[i] != nil);
        MTL_NAME(fragmentFuncs[i], @"%@", fragmentNames[i]);
    }

    // Clear Functions
    id<MTLFunction> vertexClearFunc = [library newFunctionWithName:@"ClearVS"];
    NS_ASSERT(vertexClearFunc != nil);
    MTL_NAME(vertexClearFunc, @"ClearVS");

    id<MTLFunction> fragmentClearFunc = [library newFunctionWithName:@"ClearFS"];
    NS_ASSERT(fragmentClearFunc != nil);
    MTL_NAME(fragmentClearFunc, @"ClearFS");

    // Vertex descriptors
    const uint32_t VFPos = 0;
    const uint32_t VFColor = 1;
    const uint32_t VFTex0 = 2;
    const uint32_t VFTex1 = 4;
    const uint32_t VFTex2 = 8;
    const uint32_t VFCoverage = 16;

    MTLVertexDescriptor* vertexDescriptors[9];
    const uint8_t vFormats[] =
    {
        VFPos,
        VFPos | VFColor,
        VFPos | VFTex0,
        VFPos | VFColor | VFCoverage,
        VFPos | VFTex0  | VFCoverage,
        VFPos | VFColor | VFTex1,
        VFPos | VFTex0  | VFTex1,
        VFPos | VFColor | VFTex1 | VFTex2,
        VFPos | VFTex0  | VFTex1 | VFTex2
    };

    static_assert(NS_COUNTOF(vFormats) == NS_COUNTOF(vertexDescriptors), "Size mismatch");

    for (uint32_t i = 0; i < NS_COUNTOF(vFormats); i++)
    {
        NSUInteger offset = 0;
        vertexDescriptors[i] = [MTLVertexDescriptorClass vertexDescriptor];
        vertexDescriptors[i].attributes[0].format = MTLVertexFormatFloat2;
        vertexDescriptors[i].attributes[0].offset = offset;
        offset += 8;

        if ((vFormats[i] & VFColor) > 0)
        {
            vertexDescriptors[i].attributes[1].format = MTLVertexFormatUChar4Normalized;
            vertexDescriptors[i].attributes[1].offset = offset;
            offset += 4;
        }

        if ((vFormats[i] & VFTex0) > 0)
        {
            vertexDescriptors[i].attributes[2].format = MTLVertexFormatFloat2;
            vertexDescriptors[i].attributes[2].offset = offset;
            offset += 8;
        }

        if ((vFormats[i] & VFTex1) > 0)
        {
            vertexDescriptors[i].attributes[3].format = MTLVertexFormatFloat2;
            vertexDescriptors[i].attributes[3].offset = offset;
            offset += 8;
        }

        if ((vFormats[i] & VFTex2) > 0)
        {
            vertexDescriptors[i].attributes[4].format = MTLVertexFormatUShort4Normalized;
            vertexDescriptors[i].attributes[4].offset = offset;
            offset += 8;
        }

        if ((vFormats[i] & VFCoverage) > 0)
        {
            vertexDescriptors[i].attributes[5].format = MTLVertexFormatFloat;
            vertexDescriptors[i].attributes[5].offset = offset;
            offset += 4;
        }

        vertexDescriptors[i].layouts[0].stride = offset;
    }

    // Main Pipeline
    struct Program
    {
        int8_t vFormatIdx;
        int8_t vShaderIdx;
        int8_t fShaderIdx;
    #ifdef NS_PROFILE
        NSString* label;
    #endif
    };

    #ifdef NS_PROFILE
        #define PROGRAM(name, format, vertex, fragment) \
            programs[Shader::name] = { format, vertex, fragment, @#name }
    #else
        #define PROGRAM(name, format, vertex, fragment) \
            programs[Shader::name] = { format, vertex, fragment }
    #endif

    Program programs[Shader::Count];
    memset(programs, 255, sizeof(programs));

    PROGRAM(RGBA, 0, 0,  0);
    PROGRAM(Mask, 0, 0, -1);

    PROGRAM(Path_Solid, 1, 1, 1);
    PROGRAM(Path_Linear, 2, 2, 2);
    PROGRAM(Path_Radial, 2, 2, 3);
    PROGRAM(Path_Pattern, 2, 2, 4);

    PROGRAM(PathAA_Solid, 3, 3, 5);
    PROGRAM(PathAA_Linear, 4, 4, 6);
    PROGRAM(PathAA_Radial, 4, 4, 7);
    PROGRAM(PathAA_Pattern, 4, 4, 8);

    PROGRAM(SDF_Solid, 5, 9, 9);
    PROGRAM(SDF_Linear, 6, 10, 10);
    PROGRAM(SDF_Radial, 6, 10, 11);
    PROGRAM(SDF_Pattern, 6, 10, 12);

    PROGRAM(Image_Opacity_Solid, 5, 5, 13);
    PROGRAM(Image_Opacity_Linear, 6, 6, 14);
    PROGRAM(Image_Opacity_Radial, 6, 6, 15);
    PROGRAM(Image_Opacity_Pattern, 6, 6, 16);

    PROGRAM(Image_Shadow35V, 7, 7, 17);
    PROGRAM(Image_Shadow63V, 7, 7, 18);
    PROGRAM(Image_Shadow127V, 7, 7, 19);

    PROGRAM(Image_Shadow35H_Solid, 7, 7, 20);
    PROGRAM(Image_Shadow35H_Linear, 8, 8, 21);
    PROGRAM(Image_Shadow35H_Radial, 8, 8, 22);
    PROGRAM(Image_Shadow35H_Pattern, 8, 8, 23);

    PROGRAM(Image_Shadow63H_Solid, 7, 7, 24);
    PROGRAM(Image_Shadow63H_Linear, 8, 8, 25);
    PROGRAM(Image_Shadow63H_Radial, 8, 8, 26);
    PROGRAM(Image_Shadow63H_Pattern, 8, 8, 27);

    PROGRAM(Image_Shadow127H_Solid, 7, 7, 28);
    PROGRAM(Image_Shadow127H_Linear, 8, 8, 29);
    PROGRAM(Image_Shadow127H_Radial, 8, 8, 30);
    PROGRAM(Image_Shadow127H_Pattern, 8, 8, 31);

    PROGRAM(Image_Blur35V, 7, 7, 32);
    PROGRAM(Image_Blur63V, 7, 7, 33);
    PROGRAM(Image_Blur127V, 7, 7, 34);

    PROGRAM(Image_Blur35H_Solid, 7, 7, 35);
    PROGRAM(Image_Blur35H_Linear, 8, 8, 36);
    PROGRAM(Image_Blur35H_Radial, 8, 8, 37);
    PROGRAM(Image_Blur35H_Pattern, 8, 8, 38);

    PROGRAM(Image_Blur63H_Solid, 7, 7, 39);
    PROGRAM(Image_Blur63H_Linear, 8, 8, 40);
    PROGRAM(Image_Blur63H_Radial, 8, 8, 41);
    PROGRAM(Image_Blur63H_Pattern, 8, 8, 42);

    PROGRAM(Image_Blur127H_Solid, 7, 7, 43);
    PROGRAM(Image_Blur127H_Linear, 8, 8, 44);
    PROGRAM(Image_Blur127H_Radial, 8, 8, 45);
    PROGRAM(Image_Blur127H_Pattern, 8, 8, 46);

    #undef PROGRAM

    MTLRenderPipelineDescriptor* desc = [[MTLRenderPipelineDescriptorClass alloc] init];
    MTLPixelFormat depthFormat = stencilFormat == MTLPixelFormatStencil8 ? MTLPixelFormatInvalid : stencilFormat;

    for (uint32_t i = 0; i < NS_COUNTOF(programs); i++)
    {
        const Program& p = programs[i];

        if (p.vFormatIdx == -1)
        {
            continue;
        }

        NS_ASSERT(p.vFormatIdx < NS_COUNTOF(vertexDescriptors));
        NS_ASSERT(p.vShaderIdx < NS_COUNTOF(vertexFuncs));
        NS_ASSERT(p.fShaderIdx == -1 || programs[i].fShaderIdx < NS_COUNTOF(fragmentFuncs));

        bool disableColor = p.fShaderIdx == -1;
        Shader shader = { .v = (uint8_t)i };

        for (uint32_t j = 0; j < 256; j++)
        {
            RenderState state = { .v = (uint8_t)j };

            if (!IsValidState(shader, state))
            {
                continue;
            }

            NS_ASSERT((hash & Hash(shader, state)) == 0);
            Pipelines::InsertResult f = mPipelines.Insert(hash | Hash(shader, state));
            if (!f.second)
            {
                continue;
            }

            [desc reset];
            desc.vertexDescriptor = vertexDescriptors[p.vFormatIdx];
            desc.vertexFunction = vertexFuncs[p.vShaderIdx];
            desc.fragmentFunction = disableColor ? nil: fragmentFuncs[p.fShaderIdx];
            desc.sampleCount = sampleCount;
            desc.depthAttachmentPixelFormat = depthFormat;
            desc.stencilAttachmentPixelFormat = stencilFormat;
            desc.colorAttachments[0].pixelFormat = colorFormat;

            if (state.f.blendMode == BlendMode::SrcOver)
            {
                MTLRenderPipelineColorAttachmentDescriptor* color0 = desc.colorAttachments[0];

                color0.blendingEnabled = true;
                color0.rgbBlendOperation = MTLBlendOperationAdd;
                color0.alphaBlendOperation = MTLBlendOperationAdd;
                color0.sourceRGBBlendFactor = MTLBlendFactorOne;
                color0.sourceAlphaBlendFactor = MTLBlendFactorOne;
                color0.destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
                color0.destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
            }

            MTL_NAME(desc, @"Noesis::%@%@", p.label, state.f.blendMode == BlendMode::Src ? @"" : @"_blend");
            f.first->value = [mDevice newRenderPipelineStateWithDescriptor:desc error:&error];
            NS_ASSERT(error == 0);
        }
    }

    // Clear Pipeline
    [desc reset];
    desc.vertexFunction = vertexClearFunc;
    desc.fragmentFunction = fragmentClearFunc;
    desc.sampleCount = sampleCount;
    desc.depthAttachmentPixelFormat = depthFormat;
    desc.stencilAttachmentPixelFormat = stencilFormat;
    desc.colorAttachments[0].pixelFormat = colorFormat;
    MTL_NAME(desc, @"Noesis::Clear");

    mClearPipelines[hash] = [mDevice newRenderPipelineStateWithDescriptor:desc error:&error];
    NS_ASSERT(error == 0);

    for (uint32_t i = 0; i < NS_COUNTOF(vertexFuncs); i++)
    {
        MTL_RELEASE(vertexFuncs[i]);
    }

    for (uint32_t i = 0; i < NS_COUNTOF(fragmentFuncs); i++)
    {
        MTL_RELEASE(fragmentFuncs[i]);
    }

    MTL_RELEASE(vertexClearFunc);
    MTL_RELEASE(fragmentClearFunc);
    MTL_RELEASE(desc);
    MTL_RELEASE(library);

    Dealloc(shaders);

#ifdef NS_PROFILE
    NS_LOG_TRACE("Pipeline '0x%x' compiled in %.0f ms", hash >> 16, 1000.0 * HighResTimer::Seconds(
        HighResTimer::Ticks() - t0));
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MTLRenderDevice::Page* MTLRenderDevice::AllocatePage(DynamicBuffer& buffer)
{
    NS_ASSERT(buffer.numPages < NS_COUNTOF(buffer.pages));
    Page* page = &buffer.pages[buffer.numPages];

    page->inUse = false;
    page->object = [mDevice newBufferWithLength:buffer.size options:0];
    MTL_NAME(page->object, buffer.size == DYNAMIC_VB_SIZE ? @"Noesis::Vertices" : @"Noesis::Indices");
    NS_LOG_TRACE("Page '%s[%d]' created (%d KB)", buffer.size == DYNAMIC_VB_SIZE ?
        "Noesis::Vertices" : "Noesis::Indices", buffer.numPages, buffer.size / 1024);

    buffer.numPages++;
    return page;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::CreateBuffer(DynamicBuffer& buffer, uint32_t size)
{
    buffer.size = size;
    buffer.pos = 0;
    buffer.drawPos = 0;

    buffer.numPages = 0;
    memset(buffer.pages, 0, sizeof(buffer.pages));

    buffer.pendingPages = nullptr;
    buffer.freePages = nullptr;

    for (uint32_t i = 0; i < PREALLOCATED_DYNAMIC_PAGES; i++)
    {
        Page* page = AllocatePage(buffer);
        page->next = buffer.freePages;
        buffer.freePages = page;
    }

    NS_ASSERT(buffer.freePages != nullptr);
    buffer.currentPage = buffer.freePages;
    buffer.freePages = buffer.freePages->next;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::CreateBuffers()
{
   CreateBuffer(mDynamicVB, DYNAMIC_VB_SIZE);
   CreateBuffer(mDynamicIB, DYNAMIC_IB_SIZE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* MTLRenderDevice::MapBuffer(DynamicBuffer& buffer, uint32_t size)
{
    NS_ASSERT(size <= buffer.size);

    if (buffer.pos + size > buffer.size)
    {
        // We ran out of space in the current page, get a new one
        // Move the current one to pending and insert a GPU fence
        buffer.currentPage->inUse = true;
        Page* currentPage = buffer.currentPage;
        [mCommands addCompletedHandler:^(id<MTLCommandBuffer>)
        {
            currentPage->inUse = false;
        }];

        buffer.currentPage->next = buffer.pendingPages;
        buffer.pendingPages = buffer.currentPage;

        // If there is one free slot get it
        if (buffer.freePages != nullptr)
        {
            buffer.currentPage = buffer.freePages;
            buffer.freePages = buffer.freePages->next;
        }
        else
        {
            // Move pages already processed by GPU from pending to free
            Page** it = &buffer.pendingPages;
            while (*it != nullptr)
            {
                if ((*it)->inUse)
                {
                    it = &((*it)->next);
                }
                else
                {
                    // Once we find a processed page, the rest of pages must be also processed.
                    // Although this is not exactly true in Metal when addCompleteHandler needs
                    // to be invoked for several pages belonging to the same command buffer. Those
                    // invocations are not necessarily done in order of completion. But at the time
                    // those free pages are going to be used the inUse flag must be already false
                    Page* page = *it;
                    *it = nullptr;

                    NS_ASSERT(buffer.freePages == nullptr);
                    buffer.freePages = page;
                    break;
                }
            }

            if (buffer.freePages != nullptr)
            {
                buffer.currentPage = buffer.freePages;
                buffer.freePages = buffer.freePages->next;
            }
            else
            {
                buffer.currentPage = AllocatePage(buffer);
            }
        }

        NS_ASSERT(!buffer.currentPage->inUse);
        buffer.pos = 0;
    }

    buffer.drawPos = buffer.pos;
    buffer.pos += size;
    return (uint8_t*)[buffer.currentPage->object contents] + buffer.drawPos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::CheckMultisample()
{
    uint8_t sampleCount = 0;

    for (uint8_t i = 0; i < 16; i++)
    {
        if ([mDevice supportsTextureSampleCount: i + 1])
        {
            sampleCount = i + 1;
        }

        mSampleCounts[i] = sampleCount;
    }

    NS_ASSERT(mSampleCounts[0] == 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::FillCaps(bool sRGB)
{
    CheckMultisample();

    mCaps.centerPixelOffset = 0.0f;
    mCaps.linearRendering = sRGB;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MTLRenderDevice::BindAPI()
{
    MTLTextureDescriptorClass = NSClassFromString(@"MTLTextureDescriptor");
    MTLRenderPipelineDescriptorClass = NSClassFromString(@"MTLRenderPipelineDescriptor");
    MTLRenderPassDescriptorClass = NSClassFromString(@"MTLRenderPassDescriptor");
    MTLDepthStencilDescriptorClass = NSClassFromString(@"MTLDepthStencilDescriptor");
    MTLVertexDescriptorClass = NSClassFromString(@"MTLVertexDescriptor");
    MTLSamplerDescriptorClass = NSClassFromString(@"MTLSamplerDescriptor");

    NS_ASSERT(MTLTextureDescriptorClass != nullptr);
    NS_ASSERT(MTLRenderPipelineDescriptorClass != nullptr);
    NS_ASSERT(MTLRenderPassDescriptorClass != nullptr);
    NS_ASSERT(MTLDepthStencilDescriptorClass != nullptr);
    NS_ASSERT(MTLVertexDescriptorClass != nullptr);
    NS_ASSERT(MTLSamplerDescriptorClass != nullptr);
}
