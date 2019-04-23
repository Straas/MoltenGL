/*
 * mglGLKitDataTypes.h
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


/* This file contains convenient functions for converting between GLKit and Metal data types. */

#ifdef __cplusplus
extern "C" {
#endif	//  __cplusplus
	
#import "mglEnv.h"
#import <GLKit/GLKView.h>
#import <Metal/Metal.h>


/**
 * Returns the MTLPixelFormat that matches the specified GLKViewDrawableColorFormat,
 * or returns MTLPixelFormatInvalid if a match could not be found.
 */
MTLPixelFormat mglMTLPixelFormatFromGLKViewDrawableColorFormat(GLKViewDrawableColorFormat glkFormat);

/**
 * Returns the GLKViewDrawableColorFormat that matches the specified MTLPixelFormat,
 * or returns GLKViewDrawableColorFormatRGBA8888 if a match could not be found.
 */
GLKViewDrawableColorFormat mglGLKViewDrawableColorFormatFromMTLPixelFormat(MTLPixelFormat mtlFormat);

/**
 * Returns the MTLPixelFormat that matches the specified GLKViewDrawableDepthFormat,
 * or returns MTLPixelFormatInvalid if a match could not be found.
 */
MTLPixelFormat mglMTLPixelFormatFromGLKViewDrawableDepthFormat(GLKViewDrawableDepthFormat glkFormat);

/**
 * Returns the GLKViewDrawableDepthFormat that matches the specified MTLPixelFormat,
 * or returns GLKViewDrawableDepthFormatNone if a match could not be found.
 */
GLKViewDrawableDepthFormat mglGLKViewDrawableDepthFormatFromMTLPixelFormat(MTLPixelFormat mtlFormat);

/**
 * Returns the MTLPixelFormat that matches the specified GLKViewDrawableStencilFormat,
 * or returns MTLPixelFormatInvalid if a match could not be found.
 */
MTLPixelFormat mglMTLPixelFormatFromGLKViewDrawableStencilFormat(GLKViewDrawableStencilFormat glkFormat);

/**
 * Returns the GLKViewDrawableStencilFormat that matches the specified MTLPixelFormat,
 * or returns GLKViewDrawableStencilFormatNone if a match could not be found.
 */
GLKViewDrawableStencilFormat mglGLKViewDrawableStencilFormatFromMTLPixelFormat(MTLPixelFormat mtlFormat);

/**
 * Returns the Metal sample count that matches the specified GLKViewDrawableMultisample,
 * or returns 1 if a match could not be found.
 */
NSUInteger mglSampleCountFromGLKViewDrawableMultisample(GLKViewDrawableMultisample glkMultisample);

/**
 * Returns the GLKViewDrawableMultisample that matches the specified sample count,
 * or returns GLKViewDrawableMultisampleNone if a match could not be found.
 */
GLKViewDrawableMultisample mglGLKViewDrawableMultisampleFromSampleCount(NSUInteger sampleCount);

#ifdef __cplusplus
}
#endif	//  __cplusplus
