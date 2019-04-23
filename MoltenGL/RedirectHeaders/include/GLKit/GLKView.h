/*
 * GLKView.h
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


#import <MoltenGL/mglEnv.h>
#import "../../orig/GLKit/GLKView.h"


/**
 * MGLGLKView overrides the functionality of GLKView, using Metal.
 *
 * If Metal is not available on the platform, or has not been activated via the glOpenGLImplMGL()
 * function, attempting to instantiate an instance of MGLGLKView will actually return an instance
 * of the original GLKView class, permitting normal OpenGL functionality.
 */
MLN_PUBLIC_SYMBOL @interface MGLGLKView : GLKView
@end

/**
 * In any files that import this header file, redefine all references to GLKView as MGLGLKView instead.
 * This is done after class definition to allow MGLGLView to subclass native GLKView.
 */
#if (MGL_SUPPORT_OPENGL_ON_METAL || MLN_MACOS)
#	define GLKView		MGLGLKView
#endif
