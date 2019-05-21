/*
 * mglMetalState.h
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


/* This file contains convenient functions for accessing Metal components during execution. */

#ifdef __cplusplus
extern "C" {
#endif	//  __cplusplus
	
#import "mglEnv.h"
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <OpenGLES/gltypes.h>


#pragma mark Metal device

/** Returns the MTLDevice instance used by the MoltenGL engine, lazily creating it if needed. */
id<MTLDevice> mglGetMTLDevice();


#pragma mark Resources

/**
 * Returns the Metal MTLTexture object underlying the texture currently bound to the target.
 *
 * The target parameter must be one of GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP.
 */
id<MTLTexture> mglTexGetMTLTexture(GLenum target);

/**
 * Sets the Metal MTLTexture object underlying the texture currently bound to the target
 * to the specified MTLTexture.
 *
 * The MTLTexture textureType must match the target type. The pixelFormat, pixelType,
 * and size properties of the OpenGL texture will be updated to match the incoming MTLTexture.
 * The target parameter must be one of GL_TEXTURE_2D or GL_TEXTURE_CUBE_MAP.
 */
void mglTexSetMTLTexture(GLenum target, id<MTLTexture> mtlTex);

	
#pragma mark Shaders

/**
 * Returns the Metal MTLFunction of the specified shader type from the shader program that
 * was bound to the context through the most recent call to glUseProgram, or returns nil 
 * if no shader program is currently bound.
 *
 * The shaderType parameter must be one of GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
 */
id<MTLFunction> mglGetMTLFunction(GLenum shaderType);

	
#pragma mark Rendering

/**
 * Returns the MTLCommandQueue instance that is used by the current rendering context.
 *
 * The MTLCommandQueue is associated with the current rendering context for this thread.
 *
 * You can use this function to help manage the rendering pipeline state when combining
 * Metal rendering and OpenGL rendering via MoltenGL.
 */
id<MTLCommandQueue> mglGetMTLCommandQueue();

/**
 * Returns the id<CAMetalDrawable> instance that is currently bound to the Metal engine.
 *
 * The id<CAMetalDrawable> is associated with the color attachment of the primary framebuffer
 * associated with the CALayer of the UIView. This function returns the id<CAMetalDrawable> 
 * instance associated with the color attachment of the currenly bound framebuffer.
 *
 * This function will return nil if the currently bound framebuffer does not have a color
 * attachment, or if that color attachment is not associated with the CALayer of the UIView.
 *
 * You can use this function to help manage the rendering pipeline state when combining
 * Metal rendering and OpenGL rendering via MoltenGL.
 */
id<CAMetalDrawable> mglGetCAMetalDrawable();

/**
 * Returns the Metal command buffer to which rendering commands are currently being directed in
 * the current context. The returned command buffer is lazily created if it does not already exist.
 *
 * You can use this function to help manage the rendering pipeline state when combining
 * Metal rendering and OpenGL rendering via MoltenGL.
 */
id<MTLCommandBuffer> mglGetMTLCommandBuffer();
	
/**
 * Returns the Metal command encoder that is currently being used to encode rendering
 * operations during the current render pass. The returned command encoder is lazily 
 * created if it does not already exist.
 *
 * Since only a single command encoder may be active at any one time, when the command 
 * encoder returned by this function is created, the BLIT command encoder (available 
 * from the mglGetMTLBlitCommandEncoder function) will be ended (and will subsequently
 * be re-created the next time is it accessed).
 *
 * You can use this function to help manage the rendering pipeline state when combining
 * Metal rendering and OpenGL rendering via MoltenGL.
 */
id<MTLRenderCommandEncoder> mglGetMTLRenderCommandEncoder();

/**
 * Returns the Metal command encoder that is currently being used to encode texture-copying
 * BitBLT operations. The returned command encoder is lazily created if it does not already exist.
 *
 * Since only a single command encoder may be active at any one time, when the command
 * encoder returned by this function is created, the render command encoder (available
 * from the mglGetMTLRenderCommandEncoder function) will be ended (and will subsequently
 * be re-created the next time is it accessed).
 *
 * You can use this function to help manage the rendering pipeline state when combining
 * Metal rendering and OpenGL rendering via MoltenGL.
 */
id<MTLBlitCommandEncoder> mglGetMTLBlitCommandEncoder();


#ifdef __cplusplus
}
#endif	//  __cplusplus
