/*
 * mglext.h
 *
 * Copyright (c) 2014-2019 The Brenwill Workshop Ltd. All rights reserved.
 * http://www.brenwill.com
 *
 * Use of this document is governed by the MoltenGL License Agreement, as included
 * in the MoltenGL distribution package. CAREFULLY READ THAT LICENSE AGREEMENT BEFORE
 * READING AND USING THIS DOCUMENT. BY READING OR OTHERWISE USING THIS DOCUMENT,
 * YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS AND CONDITIONS OF THAT LICENSE
 * AGREEMENT. IF YOU DO NOT ACCEPT THE TERMS AND CONDITIONS OF THAT LICENSE AGREEMENT,
 * DO NOT READ OR USE THIS DOCUMENT.
 */

/** @file */	// Doxygen marker

/*
 * This file contains MoltenGL extensions to OpenGL, which add additional OpenGL enumeration
 * values and additional OpenGL-style functions to manage extended MoltenGL state.
 */

#ifdef __cplusplus
extern "C" {
#endif	//  __cplusplus
	
#import "mglEnv.h"
#import <OpenGLES/gltypes.h>

	
#pragma mark MoltenGL extension enumerations

/** GL_FRAMEBUFFER_UNDEFINED is a standard OpenGL enumeration value that is not defined in all implementations. */
#ifndef GL_FRAMEBUFFER_UNDEFINED
#	define GL_FRAMEBUFFER_UNDEFINED						0x8219
#endif


#pragma mark -
#pragma mark Additional MoltenGL capabilities

/**
 * This capability controls the basic functionality of MoltenGL.
 *
 * If this capability is enabled, OpenGL behaviour will be provided by Metal. If this
 * capability is disabled, OpenGL behaviour will be provided by the native OpenGL engine.
 *
 * By default, this capability is enabled if the device and operating system support Metal,
 * otherwise this capability is disabled. Usually, you do not need to set this capability.
 *
 * If you want to change the value of this property, you MUST do so at application startup
 * before the OpenGL context is created, and before any other OpenGL functions are called.
 *
 * You can query the current value of this capability using the glIsEnabled() or glGet...() 
 * functions to return a boolean value indicating whether OpenGL behaviour is being provided 
 * by Metal.
 */
#define GL_OPENGL_USE_METAL_MGL							0x6000


#pragma mark Debug capabilities

/**
 * This is a convenience capability that turns on several debug features for use during
 * development time.
 *
 * Enabling this capability enables the following individual capabilities:
 *   - GL_ERROR_ASSERTION_MGL
 *   - GL_ENSURE_VERTEX_BUFFER_SIZE_ON_DRAW_MGL
 *   - GL_LOG_SHADER_CONVERSION_SOURCE_CODE_MGL
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is disabled by default.
 */
#define GL_DEBUG_MODE_MGL								0x6001

/**
 * MoltenGL will test for, and record, standard OpenGL errors when the conditions for those errors
 * arise. These errors can be retrieved and cleared using the standard glGetError() function.
 *
 * This capability setting indicates whether MoltenGL should also raise an assertion when an
 * OpenGL error condition occurs. Enabling this capability can often help you track down the
 * source of these types of errors.
 *
 * If this capability is enabled, assertions on OpenGL errors will occur only with the Debug
 * build of the MoltenGL library. Assertions will never be raised with the Release build of
 * the MoltenGL library.
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is disabled by default.
 */
#define GL_ERROR_ASSERTION_MGL							0x6002

/**
 * This capability setting indicates whether the sizes of vertex buffers should be validated
 * during rendering.
 *
 * This capability may be enabled or disabled using the standard glEnable() and glDisable() functions.
 *
 * Metal requires that all vertex buffers have a known size when allocated, whereas OpenGL permits
 * the use of an open-ended address space when drawing both indexed, and non-indexed, vertices.
 *
 * Therefore, for any vertices in memory, a temporary buffer is created and populated from the
 * vertices in memory during each draw call. The length of that buffer is determined by multiplying
 * the stride of the vertices by the number of vertices that will be accessed during drawing.
 *
 * For indexed vertices, the number of vertices used in a draw call must be found by iterating
 * through the vertex indices to retrieve the largest index value. If this capability is enabled,
 * this iteration of the vertex indices will be performed on each draw call. If this capability
 * is disabled, it is assumed that the number of vertices will be less than or equal to the number
 * of vertex indices, which is typically the case. In most common rending situations, the number
 * of vertex indices is greater than the number of vertices, and the iteration of the vertex
 * indices can be skipped by disabling this capability.
 *
 * For vertices held in an OpenGL buffer object (VBO), if this capability is enabled, the size
 * of the OpenGL buffer is validated against the length expected by multiplying the stride of
 * the vertices by the number of vertices that will be accessed during drawing. For indexed
 * vertices, the number of vertices used in that validation must be found by iterating through
 * the vertex indices to retrieve the largest index value. This validation step, and the
 * iteration of the vertex indices, can be skipped by disabling this capability.
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is disabled by default. Enabling this capability can be useful during
 * development, but traversing the set of vertex indices for each draw call can be time
 * consuming and can affect performance. Therefore, you should always leave this capability
 * disabled in your production builds.
 */
#define GL_ENSURE_VERTEX_BUFFER_SIZE_ON_DRAW_MGL		0x6003

/**
 * This capability indicates whether the GLSL and MSL shader source code should be
 * logged to the console during runtime shader coversion, to aid in troubleshooting.
 *
 * Changing the value of this capability affects the behaviour of subsequent conversions.
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is disabled by default, indicating that shader source code will
 * not be logged to the console during runtime shader conversion.
 */
#define GL_LOG_SHADER_CONVERSION_SOURCE_CODE_MGL		0x6004


#pragma mark MoltenGL operational capabilities

/**
 * This capability indicates whether retrieval of the CAMetalDrawable for each frame should
 * be deferred to as late as possible within each frame.
 *
 * CAMetalDrawable instances are transient for each frame. During each frame, an instance is
 * retrieved from a small pool managed by the Metal framework. With this capability enabled,
 * that retrieval is deferred until the end of the rendering frame, just before the drawable
 * is displayed. This minimizes the chance the CPU will block waiting for a drawable to become
 * available from the pool.
 *
 * Enabling this capability can greatly improve the CPU throughput of each frame, but may add
 * a small overhead to the GPU. You should therefore enable this capability if your rendering
 * is bound mostly by CPU throughput, but should consider disabling this capability under any
 * of the following conditions:
 *   - Your rendering is already deferred until late in the frame loop, by design.
 *   - Your rendering is bound mostly by GPU throughput.
 *   - Your rendering is not bound by either the CPU or GPU.
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is enabled by default, indicating that retrieval of the drawable will be deferred.
 */
#define GL_DEFERRED_DRAWABLE_MGL						0x6005

/**
 * This capability indicates whether, to improve performance, the MSL shader compiler
 * will perform floating-point optimizations that may violate the IEEE 754 standard.
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is enabled by default.
 */
#define GL_METAL_SHADER_COMPILER_FAST_MATH_MGL			0x6006

/**
 * This capability indicates whether compressed PVRTC textures should be flipped vertically
 * when loaded into memory.
 *
 * The texture coordinate layout of Metal is inverted in the Y-axis relative to the 
 * coordinate layout of OpenGL. Under the same conditions, Metal textures will appear 
 * upside-down. To avoid this, MoltenGL vertically flips texture content in memory during
 * content loading and updating, and uses inverted texture coordinates on the Y-axis within
 * shaders. This last step provides consistency regardless of whether a texture is loaded
 * or generated through render-to-texture. The same Metal shader can be used with a texture
 * that was either loaded from external content or previously generated through a
 * render-to-texture operation.
 *
 * Flipping a compressed PVRTC texture can be quite expensive because, due to the complex 
 * nature of PVRTC compression, the texture must first be decompressed, flipped in memory, 
 * and then recompressed. Depending on the size of the texture, this may consume significant
 * time and memory during PVRTC texture loading.
 *
 * To avoid this overhead when loading compressed PVRTC textures, you can disable this
 * capability using the glDisable() function. In doing so, you will need to compensate 
 * for the upside-down texture under Metal, using one or other of the following techniques:
 *
 *   - Adjust your Metal shaders that use PVRTC textures so that they no longer use 
 *     inverted Y-axis texture coordinates. This means that if you use those same 
 *     shaders with non-PVRTC textures, those textures will appear upside-down.
 *
 *   - Store your PVRTC textures upside-down in their files. This will avoid the need 
 *     to flip the PVRTC texture on loading, and you can leave your shaders unchanged.
 *     However, if you need to also use the same textures when running under native 
 *     OpenGL (as on a device that doesn't support Metal), OpenGL will render those 
 *     PVRTC textures upside-down.
 *
 * You can enable or disable this capability at any time by using the glEnable() and
 * glDisable() functions, and you can query the current value of this capability using
 * the glIsEnabled() or glGet...() functions.
 *
 * This capability is enabled by default, meaning that PVRTC texture content will be 
 * flipped on loading unless this capability is disabled.
 */
#define GL_FLIP_TEXTURES_PVRTC_MGL						0x6007

/**
 * Several OpenGL texture formats are not explicitly available in Metal (eg- RGB), or the 
 * order of the RGBA components may be different between an OpenGL texture format and the
 * corresponding Metal texture format.
 *
 * This capability indicates whether MoltenGL should convert the data content of textures to 
 * a format that allows the RGBA components to be the same in both the original OpenGL format
 * and the Metal format.
 *
 * If this capability is enabled, when loading texture data, if an exact match cannot be 
 * found between the OpenGL texture format and a corresponding Metal texture format, MoltenGL
 * will use a Metal texture format that contains the same components as the OpenGL texture
 * format, but possibly in a different order, or that may contain additional components not 
 * in the original OpenGL texture format, and will swizzle the texture content from the OpenGL
 * components to the corresponding components in the Metal texture. Metal shaders using the
 * texture, will see the texture content in the expected RGBA components.
 *
 * If this capability is disabled, when loading texture data, MoltenGL will use a Metal texture
 * format whose pixels are the same size and structure as the OpenGL texture, preserving the
 * memory layout of the texture, and avoiding the need to swizzle the texture components.
 * Where a perfectly-matching Metal texture format does not exist, Metal shaders may see 
 * some texture content in unexpected RGBA components.
 *
 * As an example, OpenGL supports the GL_LUMINANCE_ALPHA texture format, which contains
 * luminance and alpha content in two bytes (or shorts, ints, floats, etc). Metal has no
 * corresponding texture format, but does support a MTLPixelFormatRG8Unorm texture format,
 * which has the same two-byte pixel structure as the OpenGL format, but any shader using
 * it must access the alpha (A) component as if it were the green (G) component in order
 * to read the value from the texture.
 *
 * In this example, if this capability is enabled, MoltenGL will use the MTLPixelFormatRGBA8Unorm
 * texture format instead, and during texture content loading will swizzle the alpha component
 * component from the GL_LUMINANCE_ALPHA content into the alpha component of the 
 * MTLPixelFormatRGBA8Unorm format, and will swizzle the luminance component of the 
 * GL_LUMINANCE_ALPHA content into all three of the RGB values of MTLPixelFormatRGBA8Unorm 
 * texture. Once completed, Metal shaders using the texture will see the luminance and alpha
 * content in the same RGBA components that the OpenGL shaders do.
 *
 * Swizzling is easier and more transparent than having to modify your Metal shaders to read
 * content from different components, but does increase the overhead during texture loading. 
 * This overhead appears as CPU effort to perform the swizzle, and in the case where the size
 * of the pixels is not the same (as in the above example), may increase the memory footprint
 * of the texture.
 *
 * This capability is initially enabled, indicating that when it can't find an exact match
 * between texture formats, MoltenGL will swizzle the OpenGL texture content into a Metal 
 * texture format that preserves the RGBA component access.
 */
#define GL_SWIZZLE_MISMATCHED_TEXTURES_MGL				0x6008

/**
 * Indicates whether GL texture objects for which content has been provided should be 
 * treated as if they will not be rendered to.
 *
 * By default, all GL textures are marked for both sampling and use as a render target.
 * However, if it is known that a texture will never be used as a render target, it can
 * be optimized within the GPU for sampling-only.
 *
 * A common use case when creating a texture for use as a render target is to leave the
 * initial content of that texture empty by not providing content during texture creation.
 *
 * While this capability is enabled, if content is provided during texture creation, that
 * texture will be marked as suitable for sampling, but not for use as a render target,
 * effectively making the texture read-only. While this capability is disabled, all newly
 * created textures will be marked for both sampling and possible use as a render target,
 * regardless of whether content is provided at texture creation time.
 *
 * This capability is disabled by default, indicating that textures will always be 
 * marked for possible use as a render target, regardless of whether content is 
 * provided at texture creation time.
 */
#define GL_OPTIMIZE_SAMPLE_ONLY_TEXTURES_MGL			0x600A

/**
 * Deprecated. Use the GL_OPTIMIZE_SAMPLE_ONLY_TEXTURES_MGL property instead.
 *
 * Enabling or disabling this capability has the exact opposite effect as
 * enabling or disabling the GL_OPTIMIZE_SAMPLE_ONLY_TEXTURES_MGL capability.
 */
#define GL_FORCE_RENDERABLE_TEXTURES_MGL				0x6009


#pragma mark MoltenGL shaders

/** This parameter is passed to the glGet...() functions to retrieve the current shader source language. */
#define GL_SHADER_SOURCE_LANG							0x6010

/** 
 * This parameter is passed to the glShaderSourceLanguageMGL() function to indicate that shader 
 * source code submitted to the glShaderSource() function should not be compiled. This is typically
 * used when the Metal shader function is set directly using the glShaderFunctionMGL() function.
 */
#define GL_SHADER_SOURCE_LANG_IGNORE					0x6011

/**
 * This parameter is passed to the glShaderSourceLanguageMGL() function to indicate that shader
 * source code submitted to the glShaderSource() function will be in the form of GLSL.
 * 
 * GLSL code submitted to the glShaderSource() function will be automatically converted to
 * the Metal Shading Language for compilation into a Metal shader function.
 */
#define GL_SHADER_SOURCE_LANG_GLSL						0x6012

/**
 * This parameter is passed to the glShaderSourceLanguageMGL() function to indicate that
 * shader source code submitted to the glShaderSource() function will be in the form of 
 * the Metal Shading Language.
 *
 * Metal code submitted to the glShaderSource() function will be compiled into a Metal shader function.
 */
#define GL_SHADER_SOURCE_LANG_METAL						0x6013

/**
 * This parameter is passed to the glShaderSourceLanguageMGL() function to indicate that
 * shader source code submitted to the glShaderSource() function could be in the form of
 * GLSL, or the Metal Shading Language, or both.
 *
 * With this setting in place, MoltenGL will use certain heuristics to determine the type
 * of source code that is submitted to the glShaderSource() function. When parsing starts,
 * source code is assumed to contain GLSL format. 
 *
 * When the parser encounters any of the following directives, any source code that follows
 * is taken to contain Metal Shading Language format:
 *   - #include <metal_stdlib>
 *   - using namespace
 *   - #pragma MoltenGL language Metal
 *
 * Similarly, when the parser encounters the following directive, any source code that 
 * follows is taken to contain GLSL format:
 *   - #pragma MoltenGL language GLSL
 *
 * And when the parser encounters the following directive, any source code that follows
 * is taken to be used by both GLSL and MSL:
 *   - #pragma MoltenGL language All
 *
 * It is therefore possible, in a single call to glShaderSource(), to submit shader source
 * code that contains BOTH GLSL and the Metal Shading Language. This allows you to use the
 * same call, and load the same shader source code, regardless of whether Metal is available
 * on the system. MoltenGL will automatically use the appropriate shader language.
 *
 * On systems that support Metal, if shader source code in the Metal Shading Language form
 * has been submitted to the shader, it will be compiled directly. If only GLSL has been 
 * submitted to the shader, it will be automatically converted to Metal Shading Language 
 * form, and compiled.
 *
 * On systems that do not support Metal, only the GLSL portion of source code submitted to
 * the shader will be compiled and used by the shader.
 */
#define GL_SHADER_SOURCE_LANG_AUTO						0x6014

/**
 * This parameter is passed to the glShaderSourceLanguageMGL() function to indicate that
 * shader source code submitted to the glShaderSource() function will contain only the 
 * name of a pre-compiled Metal shder function, instead of actual source code.
 *
 * The shader source may contain comments and whitespace, but the only other content
 * should be the name of a Metal shader function that exists in the shader library that
 * is currently bound to the context. Typically, this is the default shader library.
 */
#define GL_SHADER_SOURCE_LANG_METAL_FUNC				0x6015


#pragma mark MoltenGL state retrieval

/**
 * This parameter name can be used with the glIsEnabled() or glGet...() functions to return
 * a boolean value indicating whether OpenGL ES is available on this device. OpenGL ES is 
 * available on all iOS devices.
 */
#define GL_OPENGLES_AVAILABILITY_MGL					0x6020

/**
 * This parameter name can be used with the glIsEnabled() or glGet...() functions to return
 * a boolean value indicating whether Metal is available on this device. Metal is available
 * when running iOS 8 or above on iOS devices that use a 64-bit A7 processor or above.
 */
#define GL_METAL_AVAILABILITY_MGL						0x6021

/**
 * This parameter name can be used with the glGet...() functions to retrieve the size
 * of the consumable resource pools.
 *
 * See the notes for the glConsumableResourcePoolSizeMGL function for more information
 * about resource pools.
 */
#define GL_CONSUMABLE_RESOURCE_POOL_SIZE_MGL			0x6022

/**
 * This parameter name can be used with the glGet...() functions to retrieve the index, 
 * within the consumable resource pools, of the resources to which the CPU is currently
 * populating with content.
 *
 * See the notes for the glConsumableResourcePoolSizeMGL function for more information 
 * about resource pools.
 */
#define GL_CONSUMABLE_RESOURCE_POOL_INDEX_MGL			0x6023

/**
 * This parameter name can be used with the glGetString() function to retrieve a text
 * description associated with the most recent OpenGL error (as retrieved with the 
 * glGetError() function).
 *
 * If no OpenGL error has occurred, the glGetString() function will return zero.
 *
 * Similar to the behaviour of the glGetError() function, the error text string 
 * is cleared once the glGetString() function returns. Subsequent calls to the 
 * glGetString() function will return zero until another OpenGL error occurs.
 */
#define GL_ERROR_TEXT_MGL								0x6024

/**
 * This parameter name can be used with the glGetString() function to retrieve a
 * string containing the MoltenGL version number, which will be in the form
 * "MJ.MN.PT" (eg- "3.1.4").
 *
 * The raw MoltenGL version number can also be retrieved from the MLN_VERSION 
 * macro directive in the mln_env.h file.
 */
#define GL_MOLTENGL_VERSION_STRING_MGL					0x6025

/**
 * This parameter name can be used with the glGetString() function to retrieve a
 * string containing the MoltenGL version number and build number, which will be 
 * in the form "MJ.MN.PT (build BD)" (eg- "3.1.4 (build 2)").
 *
 * The raw MoltenGL version number can also be retrieved from the MLN_VERSION
 * macro directive in the mln_env.h file.
 */
#define GL_MOLTENGL_VERSION_BUILD_STRING_MGL			0x6026

/**
 * This parameter name can be used with the glGet...() functions to retrieve the
 * ID of the shader library that is currently bound to the context.
 */
#define GL_SHADER_LIBRARY_BINDING_MGL					0x6027

/** Indicates the smallest OpenGL enumeration currently reserved for use by MoltenGL. */
#define GL_MOLTENGL_ENUM_MIN_MGL						0x6000

/** Indicates the largest OpenGL enumeration currently reserved for use by MoltenGL. */
#define GL_MOLTENGL_ENUM_MAX_MGL						0x607F


#pragma mark -
#pragma mark MoltenGL functions

#pragma mark Licensing

/**
 * Activates the specified license to enable MoltenGL features and functionality associated
 * with the specified license.
 *
 * The license consists of a null-terminated string containing the license type, a
 * null-terminated string containing the ID under which the license was purchased, the
 * date the license was purchased, and a null-terminated string containing the license
 * key assigned to the purchased license.
 *
 * In addition to the license purchase information, for any license activation to take place,
 * you must set the acceptLicenseTermsAndConditions parameter to true, to indicate that you
 * accept the terms and conditions of the MoltenGL license agreement.
 *
 * MoltenGL supports several levels of license type. Depending on the license type purchased,
 * a single MoltenGL license may be associated with one MoltenGL feature set, or it may be
 * associated with multiple MoltenGL feature sets. This function may be called multiple times
 * to accommodate licenses purchased for multiple individual feature sets.
 *
 * You can call this function at any time, before or after the OpenGL context is created,
 * but typically you will call this function during application startup. You can call this
 * function multiple times to accommodate licenses purchased for multiple individual feature
 * sets. Until a valid license is applied covering each feature set used by your application,
 * MoltenGL will operate in evaluation mode.
 *
 * Using this function is not the preferred method for activating licenses because, in a
 * team environment, it is more difficult to enter valid licenses for each developer from
 * your application code. Instead, consider using the glActivateMoltenGLLicensesMGL() function, 
 * which allows you to specify the license information through compiler build settings.
 * Using compiler build settings allows you to more easily specify the license information
 * for each developer.
 */
void glActivateMoltenGLLicenseMGL(const GLchar* licenseType,
								  const GLchar* licenseID,
								  GLuint licenseYear,
								  GLuint licenseMonth,
								  GLuint licenseDay,
								  const GLchar* licenseKey,
								  GLboolean acceptLicenseTermsAndConditions);

/**
 * This function allows you to enter MoltenGL license information using compiler build settings.
 * To use this function, configure one or more licenses using the following build settings:
 *
 *   MGL_LICENSE_TYPE
 *   MGL_LICENSE_ID
 *   MGL_LICENSE_YEAR
 *   MGL_LICENSE_MONTH
 *   MGL_LICENSE_DAY
 *   MGL_LICENSE_KEY
 *
 * Each element is defined as a build setting, and should not include quote marks.
 * For example, you might configure the following build settings:
 *
 *   MGL_LICENSE_TYPE="GLES2-Indie*2"
 *   MGL_LICENSE_ID=john.doe@example.com
 *   MGL_LICENSE_YEAR=2019
 *   MGL_LICENSE_MONTH=4
 *   MGL_LICENSE_DAY=12
 *   MGL_LICENSE_KEY=NOVOT3NGHDZ6OQSCXX4VYNXGI3QLI6Z6
 *
 * In addition to the license purchase information, for any license activation to take place,
 * you must also set the following build setting to indicate that you accept the terms and
 * conditions of the MoltenGL license agreement:
 *
 *   MGL_LICENSE_ACCEPT_TERMS_AND_CONDITIONS=1
 *
 * You can call this function at any time, before or after the OpenGL context is created,
 * but typically you will call this function during application startup.
 *
 * If you are unable to use compiler build settings to enter license information, you can use the
 * more general glActivateMoltenGLLicenseMGL() function to enter each license ID/key pair directly.
 */
static inline void glActivateMoltenGLLicensesMGL() {

	// General macros for using a build setting as a string
#	define MGL_QUOTE(name) #name
#	define MGL_STR(macro) MGL_QUOTE(macro)

#	ifndef MGL_LICENSE_ACCEPT_TERMS_AND_CONDITIONS
#		define MGL_LICENSE_ACCEPT_TERMS_AND_CONDITIONS		0
#	endif

#	if (defined(MGL_LICENSE_TYPE) && defined(MGL_LICENSE_ID) && defined(MGL_LICENSE_YEAR) && defined(MGL_LICENSE_MONTH) && defined(MGL_LICENSE_DAY) && defined(MGL_LICENSE_KEY))
	glActivateMoltenGLLicenseMGL(MGL_STR(MGL_LICENSE_TYPE), MGL_STR(MGL_LICENSE_ID), MGL_LICENSE_YEAR, MGL_LICENSE_MONTH, MGL_LICENSE_DAY, MGL_STR(MGL_LICENSE_KEY), MGL_LICENSE_ACCEPT_TERMS_AND_CONDITIONS);
#	endif
}


#pragma mark Environment

/**
 * Enables the specified OpenGL capability.
 *
 * This performs the same function as the standard OpenGL glEnable() function, 
 * but also handles the additional MoltenGL capabilities defined above, even when
 * the native OpenGL engine is active.
 */
void glEnableMGL(GLenum cap);

/**
 * Disables the specified OpenGL capability.
 *
 * This performs the same function as the standard OpenGL glDisable() function,
 * but also handles the additional MoltenGL capabilities defined above, even when
 * the native OpenGL engine is active.
 */
void glDisableMGL(GLenum cap);

/**
 * Returns whether the specified OpenGL capability is currently enabled.
 *
 * This performs the same function as the standard OpenGL glIsEnabled() function,
 * but also handles the additional MoltenGL capabilities defined above, even when
 * the native OpenGL engine is active.
 */
GLboolean glIsEnabledMGL(GLenum cap);

/**
 * Sets the size of the pool for any resources that are consumed by a rendering loop.
 *
 * GPU processing of rendering commands is performed asynchronously from CPU command requests.
 * Consumable resources, such as shader uniform values, have their values set by the CPU, and
 * must persist long enough for the GPU to complete the rendering pass that consumes them.
 * To guard against the CPU overwriting these consumable resources before they are consumed
 * by the GPU, the resources are guarded by a a semaphore lock, which causes the CPU to wait
 * until the GPU has finished with the resource.
 *
 * In order to allow the CPU to continue processing the current rendering loop while the GPU
 * is consuming the content of a previous rendering loop, these consumable resources can be
 * maintained in a pool, so that the CPU can be filling one consumable resource while the GPU
 * is consuming another. At the same time, if the CPU is consistently filling resources faster
 * than the GPU is consuming them, we don't want an ever-growing pool of resources in memory.
 * To avoid that, thie function can be used to set a limit to the size of the resource pools,
 * which sets the maximum number of copies of each consumable resource that will be allocated.
 *
 * This function defines how large the pool will be for each consumable resource. If count is
 * set to 1, only one copy of each consumable resource will exist, and the CPU will wait at the
 * beginning of each rendering loop until the GPU has consumed the resources from the previous 
 * render loop before the CPU begins filling the resources with content for the new rendering loop.
 *
 * If count is set to a value greater than one a pool of multiple copies of each consumable 
 * resource will be allocated, and these resources will be cycled through to allow the CPU to
 * continue to add content to the resources while the GPU is consuming previously added content.
 * If the CPU gets far enough ahead of the GPU that the pool for each consumable resource has
 * been exhausted, the CPU will wait at the beginning of the next rendering loop until the GPU
 * has consumed enough content that the CPU can fill the resources for the new rendering loop.
 *
 * The inital value of count is 3, which should be sufficient for most applications. For simple
 * applications, where all content is easily rendered within the timeframe of a single render
 * frame, you can reduce the count to save the allocation of unnecessary resources in the pools.
 * For more complex applications, where rendering occurs in bursts of CPU activity, you may 
 * consider increasing the count to allow the CPU to be able to move well ahead of the GPU.
 *
 * If you wish to change this value, you must do this after the OpenGL context has been created,
 * but before the first draw call is made. Changing the value of this property in the middle 
 * of a rendering loop may result in undefined behaviour.
 *
 * Setting count to zero is the same as setting it to one.
 *
 * You can query the value of this setting using the GL_CONSUMABLE_RESOURCE_POOL_SIZE_MGL
 * property name with the glGetIntegerv function.
 */
void glConsumableResourcePoolSizeMGL(GLuint count);

	
#pragma mark Shaders

/**
 * Sets the language for any shader source code that will be submitted to the 
 * glShaderSource() function.
 *
 * The language parameter may be one of the following:
 *   - GL_SHADER_SOURCE_LANG_IGNORE
 *   - GL_SHADER_SOURCE_LANG_GLSL
 *   - GL_SHADER_SOURCE_LANG_METAL
 *   - GL_SHADER_SOURCE_LANG_AUTO
 *   - GL_SHADER_SOURCE_LANG_METAL_FUNC
 *
 * If the language parameter is set to GL_SHADER_SOURCE_LANG_IGNORE, shader source code will
 * be ignored, and not compiled. If the language parameter is set to GL_SHADER_SOURCE_LANG_GLSL,
 * the shader source code will be taken to contain only GLSL code, and when Metal is active,
 * the GLSL code will be converted to the Metal Shading Language before compiling. If the 
 * language parameter is GL_SHADER_SOURCE_LANG_METAL, the shader source code will be taken
 * to contain only Metal Shader Language source code, and if Metal is active, it will be
 * compiled and used. If the language parameter is GL_SHADER_SOURCE_LANG_AUTO, the shader 
 * source code is taken to contain either, or both, GLSL and Metal Shading Language source code.
 * If the language parameter is GL_SHADER_SOURCE_LANG_METAL_FUNC, the shader source code
 * is taken to contain only the name of a pre-compiled Metal shader function from the shader
 * library that is currently bound to the context, which in most cases is the default Metal
 * shader library.
 *
 * If the language parameter is GL_SHADER_SOURCE_LANG_AUTO, MoltenGL will use certain heuristics
 * to determine the type of source code that is submitted to the glShaderSource() function. 
 * When parsing starts, source code is assumed to contain GLSL format.
 *
 * When the parser encounters any of the following directives, any source code that follows
 * is taken to contain Metal Shading Language format:
 *   - #include <metal_stdlib>
 *   - using namespace
 *   - #pragma MoltenGL language Metal
 *
 * Similarly, when the parser encounters the following directive, any source code that
 * follows is taken to contain GLSL format:
 *   - #pragma MoltenGL language GLSL
 *
 * And when the parser encounters the following directive, any source code that follows
 * is taken to be used by both GLSL and MSL:
 *   - #pragma MoltenGL language All
 *
 * It is therefore possible, in a single call to glShaderSource(), to submit shader source
 * code that contains BOTH GLSL and the Metal Shading Language, and have it separated, and
 * each used where appropriate. This allows you to use the same call, and load the same 
 * shader source code, regardless of whether Metal is available on the system. MoltenGL will
 * automatically use the appropriate shader language.
 *
 * On systems that support Metal, if shader source code in the Metal Shading Language form
 * has been submitted to the shader, it will be compiled directly. If only GLSL has been
 * submitted to the shader, it will be automatically converted to Metal Shading Language
 * form, and compiled.
 *
 * On systems that do not support Metal, only the GLSL portion of source code submitted to
 * the shader will be compiled and used by the shader.
 *
 * If the language parameter is GL_SHADER_SOURCE_LANG_METAL_FUNC, the shader source may
 * contain comments and whitespace, but the only other content shold be the name of a
 * pre-compiled Metal function from the currently-bound shader library, which in most cases,
 * this will be the default shader library.
 *
 * The GL_SHADER_SOURCE_LANG_METAL_FUNC selection effectively performs the same operation
 * as the glShaderFunctionMGL() function, and may be used in place of the glShaderFunctionMGL(),
 * when you are unable to use that function for some reason (such as with a 3rd party library)
 * but are able to establish the content of the shader source that is submitted to the
 * OpenGL environment through the glShaderSource() function.
 */
void glShaderSourceLanguageMGL(GLenum language);

/**
 * Creates an empty shader library object, and returns a non-zero value by which it can referenced.
 * A shader library is used to load and compile shader code written in the Metal Shading Language.
 *
 * Once you have a reference to a compiled shader library, you can populate a shader from a
 * function within that libary using the glShaderFunctionMGL function.
 *
 * A default shader library is available, containing any shader code pre-compiled during application
 * development time, and is designated by the ID value zero. You cannot create the default shader
 * library using this function. It is automatically created during application start-up.
 */
GLuint glCreateShaderLibraryMGL();

/**
 * Deletes the specified shader library, freeing up the memory associated with the shader 
 * library. If the currently bound shader library is deleted, the default library (ID zero)
 * will be automatically bound.
 *
 * A value of zero for shader will be silently ignored.
 */
void glDeleteShaderLibraryMGL(GLuint shaderLibrary);

/**
 * Binds the shader library object with the specified ID.
 *
 * An ID value of zero indicates the default shader library, containing any shader code 
 * pre-compiled during application development time. This default shader library is 
 * automatically created and bound during application start-up.
 */
void glBindShaderLibraryMGL(GLuint shaderLibrary);

/**
 * Populates the specified shader with compiled code from the specified function
 * contained in the shader library that is currently bound.
 *
 * The shaderFuncionName parameter must be a null-terminated string containing the name
 * of a function contained in the currently bound shader library.
 *
 * The shader code in the library function is already compiled. When using this function,
 * there is no need to call the glCompileShader() function.
 */
void glShaderFunctionMGL(GLuint shader, const GLchar* shaderFuncionName);


#pragma mark OpenGL enumerations and errors

/** Returns a C string containing the name of the specified GL enumeration code. */
const GLchar* glEnumNameMGL(GLenum gle);

/**
 * If no OpenGL error already exists, the OpenGL error state is set to the specified value.
 *
 * You can use this function in your application code if you want to mimic
 * an OpenGL error condition.
 *
 * The OpenGL error can be accessed via the glGetError() function. 
 * Once accessed via the glGetError() function, the error state is cleared.
 */
void glSetErrorMGL(GLenum glErr);

/**
 * If no OpenGL error already exists, the OpenGL error state is set to the specified 
 * value, and the error text is set to the specified formatted error text message.
 *
 * This is an extension of the glSetErrorMGL() function. You can use this function 
 * in your application code if you want to mimic an OpenGL error condition.
 *
 * The OpenGL error can be accessed via the glGetError() function.
 * Once accessed via the glGetError() function, the error state is cleared.
 *
 * The error text can be retrieved by calling glGetString(GL_ERROR_TEXT_MGL).
 * Once retrieved via the glGetString(), function, the error text is cleared.
 */
void glSetErrorWithTextMGL(GLenum glErr, const GLchar* errFmt, ...);

#ifdef __cplusplus
}
#endif	//  __cplusplus
