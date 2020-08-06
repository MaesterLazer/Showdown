#ifndef PRECISION_QUALIFIERS
    #define highp
    #define lowp
#endif

#ifdef CORE_PROFILE
    #define IN in
    #define OUT out
#else
    #define IN attribute
    #define OUT varying
#endif

IN highp vec2 attr_pos;

#ifdef HAS_COLOR
    IN lowp vec4 attr_color;
    OUT lowp vec4 color;
#endif

#ifdef HAS_UV0
    IN highp vec2 attr_tex0;
    OUT highp vec2 uv0;
#endif

#ifdef HAS_UV1
    IN highp vec2 attr_tex1;
    OUT highp vec2 uv1;
#endif

#ifdef HAS_UV2
    IN highp vec4 attr_tex2;
    OUT highp vec4 uv2;
#endif

#ifdef HAS_ST1
    OUT highp vec2 st1;
#endif

#ifdef HAS_COVERAGE
    IN lowp float attr_coverage;
    OUT lowp float coverage;
#endif

uniform highp mat4 projectionMtx;
uniform highp vec4 textureDimensions;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
    gl_Position = (vec4(attr_pos, 0, 1) * projectionMtx);

#ifdef HAS_COLOR
    color = attr_color;
#endif

#ifdef HAS_UV0
    uv0 = attr_tex0;
#endif

#ifdef HAS_UV1
    uv1 = attr_tex1;
#endif

#ifdef HAS_UV2
    uv2 = attr_tex2;
#endif

#ifdef HAS_ST1
    st1 = attr_tex1 * textureDimensions.xy;
#endif

#ifdef HAS_COVERAGE
    coverage = attr_coverage;
#endif
}