@echo off

:: OpenGL 2.1
if exist ShadersGL120.tar del ShadersGL120.tar
if exist ShadersGL120.h del ShadersGL120.h

CALL :build_vertex :build_120
CALL :build_fragment :build_120
Pack ShadersGL120.tar ShadersGL120.z
bin2h.py ShadersGL120.z Shaders >> ShadersGL120.h
del ShadersGL120.tar
del ShadersGL120.z

:: OpenGL 3.1
if exist ShadersGL140.tar del ShadersGL140.tar
if exist ShadersGL140.h del ShadersGL140.h

CALL :build_vertex :build_140
CALL :build_fragment :build_140
Pack ShadersGL140.tar ShadersGL140.z
bin2h.py ShadersGL140.z Shaders >> ShadersGL140.h
del ShadersGL140.tar
del ShadersGL140.z

:: OpenGL ES 2.0
if exist ShadersGLES2.tar del ShadersGLES2.tar
if exist ShadersGLES2.h del ShadersGLES2.h

CALL :build_vertex :build_es2
CALL :build_fragment :build_es2
Pack ShadersGLES2.tar ShadersGLES2.z
bin2h.py ShadersGLES2.z Shaders >> ShadersGLES2.h
del ShadersGLES2.tar
del ShadersGLES2.z

:: OpenGL ES 3.0
if exist ShadersGLES3.tar del ShadersGLES3.tar
if exist ShadersGLES3.h del ShadersGLES3.h

CALL :build_vertex :build_es3
CALL :build_fragment :build_es3
Pack ShadersGLES3.tar ShadersGLES3.z
bin2h.py ShadersGLES3.z Shaders >> ShadersGLES3.h
del ShadersGLES3.tar
del ShadersGLES3.z

goto :eof

:build_vertex
    CALL %* Pos_VS /vertex Shader.vert
    CALL %* PosColor_VS /vertex /D HAS_COLOR Shader.vert
    CALL %* PosTex0_VS /vertex /D HAS_UV0  Shader.vert
    CALL %* PosColorCoverage_VS /vertex /D HAS_COLOR /D HAS_COVERAGE Shader.vert
    CALL %* PosTex0Coverage_VS /vertex /D HAS_UV0 /D HAS_COVERAGE Shader.vert
    CALL %* PosColorTex1_VS /vertex /D HAS_COLOR /D HAS_UV1 Shader.vert
    CALL %* PosTex0Tex1_VS /vertex /D HAS_UV0 /D HAS_UV1 Shader.vert
    CALL %* PosColorTex1Tex2_VS /vertex /D HAS_COLOR /D HAS_UV1 /D HAS_UV2 Shader.vert
    CALL %* PosTex0Tex1Tex2_VS /vertex /D HAS_UV0 /D HAS_UV1 /D HAS_UV2 Shader.vert
    CALL %* PosColorTex1_SDF_VS /vertex /D HAS_COLOR /D HAS_UV1 /D HAS_ST1 Shader.vert
    CALL %* PosTex0Tex1_SDF_VS /vertex /D HAS_UV0 /D HAS_UV1 /D HAS_ST1 Shader.vert
    goto :eof

:build_fragment
    CALL %* RGBA_FS /fragment /D EFFECT_RGBA Shader.frag
    CALL %* Mask_FS /fragment /D EFFECT_MASK Shader.frag

    CALL %* PathSolid_FS /fragment /D EFFECT_PATH_SOLID Shader.frag
    CALL %* PathLinear_FS /fragment /D EFFECT_PATH_LINEAR Shader.frag
    CALL %* PathRadial_FS /fragment /D EFFECT_PATH_RADIAL Shader.frag
    CALL %* PathPattern_FS /fragment /D EFFECT_PATH_PATTERN Shader.frag

    CALL %* PathAASolid_FS /fragment /D EFFECT_PATH_AA_SOLID Shader.frag
    CALL %* PathAALinear_FS /fragment /D EFFECT_PATH_AA_LINEAR Shader.frag
    CALL %* PathAARadial_FS /fragment /D EFFECT_PATH_AA_RADIAL Shader.frag
    CALL %* PathAAPattern_FS /fragment /D EFFECT_PATH_AA_PATTERN Shader.frag

    CALL %* SDFSolid_FS /fragment /D EFFECT_SDF_SOLID Shader.frag
    CALL %* SDFLinear_FS /fragment /D EFFECT_SDF_LINEAR Shader.frag
    CALL %* SDFRadial_FS /fragment /D EFFECT_SDF_RADIAL Shader.frag
    CALL %* SDFPattern_FS /fragment /D EFFECT_SDF_PATTERN Shader.frag

    CALL %* ImageOpacitySolid_FS /fragment /D EFFECT_IMAGE_OPACITY_SOLID Shader.frag
    CALL %* ImageOpacityLinear_FS /fragment /D EFFECT_IMAGE_OPACITY_LINEAR Shader.frag
    CALL %* ImageOpacityRadial_FS /fragment /D EFFECT_IMAGE_OPACITY_RADIAL Shader.frag
    CALL %* ImageOpacityPattern_FS /fragment /D EFFECT_IMAGE_OPACITY_PATTERN Shader.frag

    CALL %* ImageShadow35V_FS /fragment /D EFFECT_IMAGE_SHADOW_35V Shader.frag
    CALL %* ImageShadow63V_FS /fragment /D EFFECT_IMAGE_SHADOW_63V Shader.frag
    CALL %* ImageShadow127V_FS /fragment /D EFFECT_IMAGE_SHADOW_127V Shader.frag

    CALL %* ImageShadow35HSolid_FS /fragment /D EFFECT_IMAGE_SHADOW_35H_SOLID Shader.frag
    CALL %* ImageShadow35HLinear_FS /fragment /D EFFECT_IMAGE_SHADOW_35H_LINEAR Shader.frag
    CALL %* ImageShadow35HRadial_FS /fragment /D EFFECT_IMAGE_SHADOW_35H_RADIAL Shader.frag
    CALL %* ImageShadow35HPattern_FS /fragment /D EFFECT_IMAGE_SHADOW_35H_PATTERN Shader.frag

    CALL %* ImageShadow63HSolid_FS /fragment /D EFFECT_IMAGE_SHADOW_63H_SOLID Shader.frag
    CALL %* ImageShadow63HLinear_FS /fragment /D EFFECT_IMAGE_SHADOW_63H_LINEAR Shader.frag
    CALL %* ImageShadow63HRadial_FS /fragment /D EFFECT_IMAGE_SHADOW_63H_RADIAL Shader.frag
    CALL %* ImageShadow63HPattern_FS /fragment /D EFFECT_IMAGE_SHADOW_63H_PATTERN Shader.frag

    CALL %* ImageShadow127HSolid_FS /fragment /D EFFECT_IMAGE_SHADOW_127H_SOLID Shader.frag
    CALL %* ImageShadow127HLinear_FS /fragment /D EFFECT_IMAGE_SHADOW_127H_LINEAR Shader.frag
    CALL %* ImageShadow127HRadial_FS /fragment /D EFFECT_IMAGE_SHADOW_127H_RADIAL Shader.frag
    CALL %* ImageShadow127HPattern_FS /fragment /D EFFECT_IMAGE_SHADOW_127H_PATTERN Shader.frag

    CALL %* ImageBlur35V_FS /fragment /D EFFECT_IMAGE_BLUR_35V Shader.frag
    CALL %* ImageBlur63V_FS /fragment /D EFFECT_IMAGE_BLUR_63V Shader.frag
    CALL %* ImageBlur127V_FS /fragment /D EFFECT_IMAGE_BLUR_127V Shader.frag

    CALL %* ImageBlur35HSolid_FS /fragment /D EFFECT_IMAGE_BLUR_35H_SOLID Shader.frag
    CALL %* ImageBlur35HLinear_FS /fragment /D EFFECT_IMAGE_BLUR_35H_LINEAR Shader.frag
    CALL %* ImageBlur35HRadial_FS /fragment /D EFFECT_IMAGE_BLUR_35H_RADIAL Shader.frag
    CALL %* ImageBlur35HPattern_FS /fragment /D EFFECT_IMAGE_BLUR_35H_PATTERN Shader.frag

    CALL %* ImageBlur63HSolid_FS /fragment /D EFFECT_IMAGE_BLUR_63H_SOLID Shader.frag
    CALL %* ImageBlur63HLinear_FS /fragment /D EFFECT_IMAGE_BLUR_63H_LINEAR Shader.frag
    CALL %* ImageBlur63HRadial_FS /fragment /D EFFECT_IMAGE_BLUR_63H_RADIAL Shader.frag
    CALL %* ImageBlur63HPattern_FS /fragment /D EFFECT_IMAGE_BLUR_63H_PATTERN Shader.frag

    CALL %* ImageBlur127HSolid_FS /fragment /D EFFECT_IMAGE_BLUR_127H_SOLID Shader.frag
    CALL %* ImageBlur127HLinear_FS /fragment /D EFFECT_IMAGE_BLUR_127H_LINEAR Shader.frag
    CALL %* ImageBlur127HRadial_FS /fragment /D EFFECT_IMAGE_BLUR_127H_RADIAL Shader.frag
    CALL %* ImageBlur127HPattern_FS /fragment /D EFFECT_IMAGE_BLUR_127H_PATTERN Shader.frag

    goto :eof

:: -------------------------------------------------------------------------------------------------------
:build_120
    glsl_optimizer /V 120 /Vn %* > %1.o
    tar.py ShadersGL120.tar %1.o >> ShadersGL120.h
    del %1.o
    goto :eof

:: -------------------------------------------------------------------------------------------------------
:build_140
    glsl_optimizer /V 140 /D CORE_PROFILE /Vn %* > %1.o
    tar.py ShadersGL140.tar %1.o >> ShadersGL140.h
    del %1.o
    goto :eof

:: -------------------------------------------------------------------------------------------------------
:build_es2
    glsl_optimizer /es /D PRECISION_QUALIFIERS /Vn %* > %1.o
    tar.py ShadersGLES2.tar %1.o >> ShadersGLES2.h
    del %1.o
    goto :eof

:: -------------------------------------------------------------------------------------------------------
:build_es3
    glsl_optimizer /es3 /V 300 /D CORE_PROFILE /D PRECISION_QUALIFIERS /Vn %* > %1.o
    tar.py ShadersGLES3.tar %1.o >> ShadersGLES3.h
    del %1.o
    goto :eof