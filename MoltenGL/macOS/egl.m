/*
 * egl.m
 *
 * MoltenGL
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

/**
 * This file provides an empty stub implementation of the OpenGL ES 2 EGL behaviour for use with macOS.
 *
 * When using MoltenGL on macOS on a machine that does not support Metal, or if you have
 * chosen not to use Metal (by setting the build setting MGL_SUPPORT_OPENGL_ON_METAL=0),
 * your OpenGL ES app needs to be able to access a "native" OpenGL ES engine. macOS supports
 * OpenGL by default, and so an OpenGL ES implementation must be provided for use on macOS.
 *
 * To allow your app to compile, under macOS, add this source code file to your macOS app project.
 * Do not add this file to an iOS app, as iOS already provides a native OpenGL ES engine.
 *
 * This file represents the OpenGL ES EGL behaviour required by MoltenGL when not using Metal,
 * but this default implementation does nothing. If your app requires OpenGL ES 2 EGL
 * functionality on macOS when not running Metal, you can add it here, or acquire a third-party
 * OpenGL ES EGL implementation for macOS, and link it instead of compiling and linking to this file.
 *
 * You can download a free public OpenGL ES EGL implementation for macOS from https://moltengl.com/downloads/#ogles-osx
 * Remove this file from your app project, add the downloaded libEGL.dylib dynamic 
 * library file to your app target, and in the Build Phases panel, add it to the 
 * "Link Binary With Libraries" AND "Copy Files" lists.
 */

#import <MoltenGL/mglEnv.h>

#if MLN_MACOS

#include <EGL/egl.h>
#import <Foundation/Foundation.h>

static inline void MGLUnimplementedOGLES(NSString* funcName) { NSLog(@"OpenGL ES EGL function %@() is not implemented under macOS.", funcName); }

EGLint eglGetError(void) {
	MGLUnimplementedOGLES(@"eglGetError");
	return 0;
}

EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id) {
	MGLUnimplementedOGLES(@"eglGetDisplay");
	return NULL;
}

EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor) {
	MGLUnimplementedOGLES(@"eglInitialize");
	return false;
}

EGLBoolean eglTerminate(EGLDisplay dpy) {
	MGLUnimplementedOGLES(@"eglTerminate");
	return false;
}

const char * eglQueryString(EGLDisplay dpy, EGLint name) {
	MGLUnimplementedOGLES(@"eglQueryString");
	return NULL;
}

EGLBoolean eglGetConfigs(EGLDisplay dpy, EGLConfig *configs,
			 EGLint config_size, EGLint *num_config) {
	MGLUnimplementedOGLES(@"eglGetConfigs");
	return false;
}

EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list,
			   EGLConfig *configs, EGLint config_size,
			   EGLint *num_config) {
	MGLUnimplementedOGLES(@"eglChooseConfig");
	return false;
}

EGLBoolean eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config,
			      EGLint attribute, EGLint *value) {
	MGLUnimplementedOGLES(@"eglGetConfigAttrib");
	return false;
}

EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
				  EGLNativeWindowType win,
				  const EGLint *attrib_list) {
	MGLUnimplementedOGLES(@"eglCreateWindowSurface");
	return NULL;
}

EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config,
				   const EGLint *attrib_list) {
	MGLUnimplementedOGLES(@"REPLACE");
	return NULL;
}

EGLSurface eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config,
				  EGLNativePixmapType pixmap,
				  const EGLint *attrib_list) {
	MGLUnimplementedOGLES(@"eglCreatePbufferSurface");
	return NULL;
}

EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface) {
	MGLUnimplementedOGLES(@"eglDestroySurface");
	return false;
}

EGLBoolean eglQuerySurface(EGLDisplay dpy, EGLSurface surface,
			   EGLint attribute, EGLint *value) {
	MGLUnimplementedOGLES(@"eglQuerySurface");
	return false;
}

EGLBoolean eglBindAPI(EGLenum api) {
	MGLUnimplementedOGLES(@"eglBindAPI");
	return false;
}

EGLenum eglQueryAPI(void) {
	MGLUnimplementedOGLES(@"eglQueryAPI");
	return 0;
}

EGLBoolean eglWaitClient(void) {
	MGLUnimplementedOGLES(@"eglWaitClient");
	return false;
}

EGLBoolean eglReleaseThread(void) {
	MGLUnimplementedOGLES(@"eglReleaseThread");
	return false;
}

EGLSurface eglCreatePbufferFromClientBuffer(
	      EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer,
	      EGLConfig config, const EGLint *attrib_list) {
	MGLUnimplementedOGLES(@"eglCreatePbufferFromClientBuffer");
	return NULL;
}

EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface,
			    EGLint attribute, EGLint value) {
	MGLUnimplementedOGLES(@"eglSurfaceAttrib");
	return false;
}

EGLBoolean eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer) {
	MGLUnimplementedOGLES(@"eglBindTexImage");
	return false;
}

EGLBoolean eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer) {
	MGLUnimplementedOGLES(@"eglReleaseTexImage");
	return false;
}


EGLBoolean eglSwapInterval(EGLDisplay dpy, EGLint interval) {
	MGLUnimplementedOGLES(@"eglSwapInterval");
	return false;
}


EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config,
			    EGLContext share_context,
			    const EGLint *attrib_list) {
	MGLUnimplementedOGLES(@"eglCreateContext");
	return NULL;
}

EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx) {
	MGLUnimplementedOGLES(@"eglDestroyContext");
	return false;
}

EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
			  EGLSurface read, EGLContext ctx) {
	MGLUnimplementedOGLES(@"eglMakeCurrent");
	return false;
}

EGLContext eglGetCurrentContext(void) {
	MGLUnimplementedOGLES(@"eglGetCurrentContext");
	return NULL;
}

EGLSurface eglGetCurrentSurface(EGLint readdraw) {
	MGLUnimplementedOGLES(@"eglGetCurrentSurface");
	return NULL;
}

EGLDisplay eglGetCurrentDisplay(void) {
	MGLUnimplementedOGLES(@"eglGetCurrentDisplay");
	return NULL;
}

EGLBoolean eglQueryContext(EGLDisplay dpy, EGLContext ctx,
			   EGLint attribute, EGLint *value) {
	MGLUnimplementedOGLES(@"eglQueryContext");
	return false;
}

EGLBoolean eglWaitGL(void) {
	MGLUnimplementedOGLES(@"eglWaitGL");
	return false;
}

EGLBoolean eglWaitNative(EGLint engine) {
	MGLUnimplementedOGLES(@"eglWaitNative");
	return false;
}

EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
	MGLUnimplementedOGLES(@"eglSwapBuffers");
	return false;
}

EGLBoolean eglCopyBuffers(EGLDisplay dpy, EGLSurface surface,
			  EGLNativePixmapType target) {
	MGLUnimplementedOGLES(@"eglCopyBuffers");
	return false;
}

__eglMustCastToProperFunctionPointerType eglGetProcAddress(const char *procname) {
	MGLUnimplementedOGLES(@"eglGetProcAddress");
	return NULL;
}

#endif	// MLN_MACOS
