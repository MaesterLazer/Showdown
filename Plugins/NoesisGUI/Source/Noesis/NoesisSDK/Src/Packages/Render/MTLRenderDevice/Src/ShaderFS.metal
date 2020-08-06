#include <metal_stdlib>
using namespace metal;

#if EFFECT_RGBA

#elif EFFECT_PATH_SOLID
    #define EFFECT_PATH 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1

#elif EFFECT_PATH_LINEAR
    #define EFFECT_PATH 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1

#elif EFFECT_PATH_RADIAL
    #define EFFECT_PATH 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1

#elif EFFECT_PATH_PATTERN
    #define EFFECT_PATH 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1

#elif EFFECT_PATH_AA_SOLID
    #define EFFECT_PATH_AA 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_COVERAGE 1

#elif EFFECT_PATH_AA_LINEAR
    #define EFFECT_PATH_AA 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_COVERAGE 1

#elif EFFECT_PATH_AA_RADIAL
    #define EFFECT_PATH_AA 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_COVERAGE 1

#elif EFFECT_PATH_AA_PATTERN
    #define EFFECT_PATH_AA 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_COVERAGE 1

#elif EFFECT_SDF_SOLID
    #define EFFECT_SDF 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_ST1 1

#elif EFFECT_SDF_LINEAR
    #define EFFECT_SDF 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_ST1 1

#elif EFFECT_SDF_RADIAL
    #define EFFECT_SDF 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_ST1 1

#elif EFFECT_SDF_PATTERN
    #define EFFECT_SDF 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_ST1 1

#elif EFFECT_IMAGE_OPACITY_SOLID
    #define EFFECT_IMAGE_OPACITY 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1

#elif EFFECT_IMAGE_OPACITY_LINEAR
    #define EFFECT_IMAGE_OPACITY 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1

#elif EFFECT_IMAGE_OPACITY_RADIAL
    #define EFFECT_IMAGE_OPACITY 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1

#elif EFFECT_IMAGE_OPACITY_PATTERN
    #define EFFECT_IMAGE_OPACITY 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1

#elif EFFECT_IMAGE_SHADOW_35V
    #define EFFECT_IMAGE_SHADOW_V 1
    #define GAUSSIAN_35_TAP 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_63V
    #define EFFECT_IMAGE_SHADOW_V 1
    #define GAUSSIAN_63_TAP 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 1

#elif EFFECT_IMAGE_SHADOW_127V
    #define EFFECT_IMAGE_SHADOW_V 1
    #define GAUSSIAN_127_TAP 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 1

#elif EFFECT_IMAGE_SHADOW_35H_SOLID
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_35H_LINEAR
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_35H_RADIAL
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_35H_PATTERN
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_63H_SOLID
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_63H_LINEAR
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_63H_RADIAL
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_63H_PATTERN
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_127H_SOLID
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_127H_LINEAR
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_127H_RADIAL
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_SHADOW_127H_PATTERN
    #define EFFECT_IMAGE_SHADOW_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_35V
    #define EFFECT_IMAGE_BLUR_V 1
    #define GAUSSIAN_35_TAP 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_63V
    #define EFFECT_IMAGE_BLUR_V 1
    #define GAUSSIAN_63_TAP 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 1

#elif EFFECT_IMAGE_BLUR_127V
    #define EFFECT_IMAGE_BLUR_V 1
    #define GAUSSIAN_127_TAP 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 1

#elif EFFECT_IMAGE_BLUR_35H_SOLID
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_35H_LINEAR
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_35H_RADIAL
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_35H_PATTERN
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_35_TAP 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_63H_SOLID
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_63H_LINEAR
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_63H_RADIAL
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_63H_PATTERN
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_63_TAP 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_127H_SOLID
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_SOLID 1
    #define HAS_COLOR 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_127H_LINEAR
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_LINEAR 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_127H_RADIAL
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_RADIAL 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2

#elif EFFECT_IMAGE_BLUR_127H_PATTERN
    #define EFFECT_IMAGE_BLUR_H 1
    #define GAUSSIAN_127_TAP 1
    #define PAINT_PATTERN 1
    #define HAS_UV0 1
    #define HAS_UV1 1
    #define HAS_UV2 2


#else
    #error No valid effect defined
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SDF_SCALE 7.96875h
#define SDF_BIAS 0.50196078431h
#define SDF_AA_FACTOR 0.65h
#define SDF_BASE_MIN 0.125h
#define SDF_BASE_MAX 0.25h
#define SDF_BASE_DEV -0.65h

struct U0
{
#if EFFECT_RGBA
    float4 rgba;
#endif

#if PAINT_RADIAL
    packed_float4 radialGrad[2];
#endif

#if PAINT_LINEAR || PAINT_RADIAL || PAINT_PATTERN
    float opacity;
#endif
};

struct U1
{
    float2 textureSize;
};

struct U2
{
#if EFFECT_IMAGE_SHADOW_V || EFFECT_IMAGE_BLUR_H || EFFECT_IMAGE_BLUR_V
    float blurSize;
#endif

#if EFFECT_IMAGE_SHADOW_H
    packed_float4 shadowColor;
    float blurSize;
    packed_float2 shadowOffset;
#endif    
};

struct In
{
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

#if HAS_ST1
    float2 st1;
#endif

#if HAS_COVERAGE
    half coverage;
#endif
};

#if GAUSSIAN_35_TAP
    #define GAUSSIAN_NUM_SAMPLES 9
    #define DECLARE_SAMPLES \
        const half w[GAUSSIAN_NUM_SAMPLES] = \
        { \
            0.10855, 0.13135, 0.10406, 0.07216, 0.04380, 0.02328, 0.01083, 0.00441, 0.00157 \
        }; \
        const half o[GAUSSIAN_NUM_SAMPLES] = \
        { \
            0.66293, 2.47904, 4.46232, 6.44568, 8.42917, 10.41281, 12.39664, 14.38070, 16.36501 \
        };
#endif

#if GAUSSIAN_63_TAP
    #define GAUSSIAN_NUM_SAMPLES 16
    #define DECLARE_SAMPLES \
        const half w[GAUSSIAN_NUM_SAMPLES] = \
        { \
            0.05991, 0.07758, 0.07232, 0.06476, 0.05571, 0.04604, 0.03655, 0.02788, 0.02042, 0.01438, \
            0.00972, 0.00631, 0.00394, 0.00236, 0.00136, 0.00075 \
        }; \
        const half o[GAUSSIAN_NUM_SAMPLES] = \
        { \
            0.66555, 2.49371, 4.48868, 6.48366, 8.47864, 10.47362, 12.46860, 14.46360, 16.45860, 18.45361, \
            20.44863, 22.44365, 24.43869, 26.43375, 28.42881, 30.42389 \
        };
#endif

#if GAUSSIAN_127_TAP
    #define GAUSSIAN_NUM_SAMPLES 32
    #define DECLARE_SAMPLES \
        const half w[GAUSSIAN_NUM_SAMPLES] = \
        { \
            0.02954, 0.03910, 0.03844, 0.03743, 0.03609, 0.03446, 0.03259, 0.03052, 0.02830, 0.02600, \
            0.02365, 0.02130, 0.01900, 0.01679, 0.01469, 0.01272, 0.01092, 0.00928, 0.00781, 0.00651, \
            0.00537, 0.00439, 0.00355, 0.00285, 0.00226, 0.00178, 0.00138, 0.00107, 0.00081, 0.00062, \
            0.00046, 0.00034 \
        }; \
        const half o[GAUSSIAN_NUM_SAMPLES] = \
        { \
            0.66640, 2.49848, 4.49726, 6.49605, 8.49483, 10.49362, 12.49240, 14.49119, 16.48997, 18.48876, \
            20.48754, 22.48633, 24.48511, 26.48390, 28.48268, 30.48147, 32.48026, 34.47904, 36.47783, 38.47662, \
            40.47540, 42.47419, 44.47298, 46.47176, 48.47055, 50.46934, 52.46813, 54.46692, 56.46571, 58.46450, \
            60.46329, 62.46208 \
        };
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fragment half4 FNAME(In i [[ stage_in ]], constant U0& u0 [[ buffer(0) ]], constant U1& u1 [[ buffer(1) ]], constant U2& u2 [[ buffer(2) ]],
    texture2d<half> pattern [[ texture(0) ]], sampler patternSampler [[ sampler(0) ]],
    texture2d<half> ramps   [[ texture(1) ]], sampler rampsSampler   [[ sampler(1) ]],
    texture2d<half> image   [[ texture(2) ]], sampler imageSampler   [[ sampler(2) ]],
    texture2d<half> glyphs  [[ texture(3) ]], sampler glyphsSampler  [[ sampler(3) ]],
    texture2d<half> shadow  [[ texture(4) ]], sampler shadowSampler  [[ sampler(4) ]]
    )
{
    /////////////////////////////////////////////////////
    // Fetch paint color and opacity
    /////////////////////////////////////////////////////
    #if PAINT_SOLID
        half4 paint = i.color;
        half opacity_ = 1.0h;

    #elif PAINT_LINEAR
        half4 paint = ramps.sample(rampsSampler, i.uv0);
        half opacity_ = u0.opacity;

    #elif PAINT_RADIAL
        half dd = u0.radialGrad[1][1] * i.uv0.x - u0.radialGrad[1][2] * i.uv0.y;
        half uu = u0.radialGrad[0][0] * i.uv0.x + u0.radialGrad[0][1] * i.uv0.y + u0.radialGrad[0][2] * 
            sqrt(u0.radialGrad[0][3] * i.uv0.x * i.uv0.x + u0.radialGrad[1][0] * i.uv0.y * i.uv0.y - dd * dd);
        half4 paint = ramps.sample(rampsSampler, float2(uu, u0.radialGrad[1][3]));
        half opacity_ = u0.opacity;

    #elif PAINT_PATTERN
        half4 paint = pattern.sample(patternSampler, i.uv0);
        half opacity_ = u0.opacity;
    #endif

    /////////////////////////////////////////////////////
    // Apply selected effect
    /////////////////////////////////////////////////////
    #if EFFECT_RGBA
        return (half4)u0.rgba;

    #elif EFFECT_PATH
        return opacity_ * paint;

    #elif EFFECT_PATH_AA
        return (opacity_ * i.coverage) * paint;

    #elif EFFECT_IMAGE_OPACITY
        return image.sample(imageSampler, i.uv1) * (opacity_ * paint.a);

    #elif EFFECT_IMAGE_SHADOW_V
        half alpha = 0.0h;
        half2 dir = half2(0.0h, u2.blurSize * u1.textureSize.y);

        DECLARE_SAMPLES
    
        for (int x = 0; x < GAUSSIAN_NUM_SAMPLES; x++)
        {
            half2 uvOffset = o[x] * dir;
            alpha += w[x] * 
            (
                image.sample(imageSampler, clamp(i.uv1 + float2(uvOffset), i.uv2.xy, i.uv2.zw)).a + 
                image.sample(imageSampler, clamp(i.uv1 - float2(uvOffset), i.uv2.xy, i.uv2.zw)).a
            );
        }

        return half4(0, 0, 0, alpha);

    #elif EFFECT_IMAGE_SHADOW_H
        half alpha = 0.0h;
        half2 dir = half2(u2.blurSize * u1.textureSize.x, 0.0h);
        half2 offset = half2(u2.shadowOffset[0] * u1.textureSize.x, u2.shadowOffset[1] * u1.textureSize.y);

        DECLARE_SAMPLES

        for (int x = 0; x < GAUSSIAN_NUM_SAMPLES; x++)
        {
            half2 uvOffset = o[x] * dir;
            alpha += w[x] * 
            (
                shadow.sample(shadowSampler, clamp(i.uv1 - float2(offset + uvOffset), i.uv2.xy, i.uv2.zw)).a +
                shadow.sample(shadowSampler, clamp(i.uv1 - float2(offset - uvOffset), i.uv2.xy, i.uv2.zw)).a
            );
        }

        half4 img = image.sample(imageSampler, clamp(i.uv1, i.uv2.xy, i.uv2.zw));
        return (img + (1.0h - img.a) * ((half4)u2.shadowColor * alpha)) * (opacity_ * paint.a);

    #elif defined(EFFECT_IMAGE_BLUR_V)
        half4 color = half4(0);
        half2 dir = half2(0.0h, u2.blurSize * u1.textureSize.y);

        DECLARE_SAMPLES

        for (int x = 0; x < GAUSSIAN_NUM_SAMPLES; x++)
        {
            half2 uvOffset = o[x] * dir;
            color += w[x] * 
            (
                image.sample(imageSampler, clamp(i.uv1 + float2(uvOffset), i.uv2.xy, i.uv2.zw)) + 
                image.sample(imageSampler, clamp(i.uv1 - float2(uvOffset), i.uv2.xy, i.uv2.zw))
            );
        }

        return color;

    #elif defined(EFFECT_IMAGE_BLUR_H)
        half4 color = half4(0);
        half2 dir = half2(u2.blurSize * u1.textureSize.x, 0.0h);

        DECLARE_SAMPLES

        for (int x = 0; x < GAUSSIAN_NUM_SAMPLES; x++)
        {
            half2 uvOffset = o[x] * dir;
            color += w[x] * 
            (
                image.sample(imageSampler, clamp(i.uv1 + float2(uvOffset), i.uv2.xy, i.uv2.zw)) + 
                image.sample(imageSampler, clamp(i.uv1 - float2(uvOffset), i.uv2.xy, i.uv2.zw))
            );
        }

        return color * (opacity_ * paint.a);

    #elif EFFECT_SDF
        half4 color = glyphs.sample(glyphsSampler, i.uv1);
        half distance = SDF_SCALE * (color.r - SDF_BIAS);
        half2 grad = (half2)dfdx(i.st1);

        half gradLen = length(grad);
        half scale = 1.0h / gradLen;
        half base = SDF_BASE_DEV * (1.0h - (clamp(scale, SDF_BASE_MIN, SDF_BASE_MAX) - SDF_BASE_MIN) / (SDF_BASE_MAX - SDF_BASE_MIN));
        half range = SDF_AA_FACTOR * gradLen;
        half alpha = smoothstep(base - range, base + range, distance);
        return (alpha * opacity_) * paint;
        
    #endif
}
