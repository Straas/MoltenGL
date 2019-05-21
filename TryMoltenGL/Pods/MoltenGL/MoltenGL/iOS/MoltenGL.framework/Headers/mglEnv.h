/*
 * mglEnv.h
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

#ifndef __mglEnv_h_
#define __mglEnv_h_ 1

#ifdef __cplusplus
extern "C" {
#endif	//  __cplusplus

#include "mln_env.h"

/**
 * Compiler build setting that determines whether the framework should support OpenGL
 * emulation on Metal.
 *
 * Enabling this build setting replaces the standard OpenGL functions with alternates 
 * that will use Metal for OpenGL functionality if Metal is available.
 *
 * Disabling this build setting will leave the original OpenGL functions in place, 
 * bypassing the ability to use Metal for OpenGL functionality.
 *
 * By default, this build setting is turned on when the platform architecture supports Metal,
 * as identified by the MGL_ARCH_SUPPORTS_METAL compiler build setting. Typically, you will
 * leave this build setting with its default value (otherwise there may be no reason to include
 * this framework in your app). However, during development time, you can disable this setting 
 * to revert to standard OpenGL functionality in order to compare the behaviour or performance 
 * of this framework against the native OpenGL library.
 */
#ifndef MGL_SUPPORT_OPENGL_ON_METAL
#	define MGL_SUPPORT_OPENGL_ON_METAL		(MLN_ARCH_SUPPORTS_METAL)
#endif



// Legacy macro definitions:

#define MGL_MAKE_VERSION(major, minor, patch, build)    MLN_MAKE_VERSION(major, minor, patch, build)
#define MGL_VERSION                                     MLN_VERSION

#ifndef MGL_IOS
#	define MGL_IOS      MLN_IOS
#endif

#ifndef MGL_MACOS
#	define MGL_MACOS	MLN_MACOS
#endif

#ifndef MGL_ARCH_SUPPORTS_METAL
#   define MGL_ARCH_SUPPORTS_METAL      MLN_ARCH_SUPPORTS_METAL
#endif

#define MGL_PUBLIC_SYMBOL		MLN_PUBLIC_SYMBOL


#ifdef __cplusplus
}
#endif	//  __cplusplus

#endif

