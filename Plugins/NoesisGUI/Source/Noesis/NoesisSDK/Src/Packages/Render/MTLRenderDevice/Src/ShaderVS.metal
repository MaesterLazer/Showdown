#include <metal_stdlib>
using namespace metal;

struct In
{
#if HAS_POSITION
    float2 position [[ attribute(0) ]];
#endif

#if HAS_COLOR
    half4 color [[ attribute(1) ]];
#endif

#if HAS_UV0
    float2 uv0 [[ attribute(2) ]];
#endif

#if HAS_UV1
    float2 uv1 [[ attribute(3) ]];
#endif

#if HAS_UV2
    float4 uv2 [[ attribute(4) ]];
#endif

#if HAS_COVERAGE
    half coverage [[ attribute(5) ]];
#endif
};

struct Out
{
#if HAS_POSITION
    float4 position [[ position ]];
#endif

#if HAS_COLOR
    half4 color;
#endif

#if HAS_UV0
    float2 uv0;
#endif

#if HAS_UV1
    float2 uv1;
#endif

#if HAS_UV2
    float4 uv2;
#endif

#ifdef HAS_ST1
    float2 st1;
#endif

#if HAS_COVERAGE
    half coverage;
#endif
};

struct U0
{
   float4x4 projectionMtx;
};

struct U1
{
    float2 textureSize;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vertex Out FNAME(In i [[ stage_in ]], constant U0& u0 [[ buffer(1) ]], constant U1& u1 [[ buffer(2) ]])
{
    Out o;

#if HAS_POSITION
    o.position = (float4(i.position, 0, 1) * u0.projectionMtx);
#endif

#if HAS_COLOR
    o.color = i.color;
#endif

#if HAS_UV0
    o.uv0 = i.uv0;
#endif

#if HAS_UV1
    o.uv1 = i.uv1;
#endif

#if HAS_UV2
    o.uv2 = i.uv2;
#endif

#if HAS_ST1
    o.st1 = i.uv1 * u1.textureSize.xy;
#endif

#if HAS_COVERAGE
    o.coverage = i.coverage;
#endif

    return o;
}
