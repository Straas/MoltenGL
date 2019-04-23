/*
 * mglDataTypes.h
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


/* This file contains convenient functions for converting between OpenGL and Metal data types. */

#ifdef __cplusplus
extern "C" {
#endif	//  __cplusplus
	
#import "mglEnv.h"
#import <OpenGLES/gltypes.h>
#import <Metal/Metal.h>


#pragma mark Pixel formats

/**
 * Returns the size in bytes for each pixel encoded in the specified MTLPixelFormat.
 *
 * Returns 1 if the size could not be determined.
 */
GLsizei mglMTLPixelFormatSizeInBytes(MTLPixelFormat pixelFormat);

/**
 * Returns the size in bytes for each pixel encoded in the specified OpenGL format and type.
 *
 * Returns 1 if the size could not be determined.
 */
GLsizei mglOpenGLPixelFormatSizeInBytes(GLenum pixelFormat, GLenum pixelType);

/** Returns the size, in bits, of the red component of the specified Metal pixel format. */
GLsizei mglMTLPixelFormatBitCountRed(MTLPixelFormat pixelFormat);

/** Returns the size, in bits, of the green component of the specified Metal pixel format. */
GLsizei mglMTLPixelFormatBitCountGreen(MTLPixelFormat pixelFormat);

/** Returns the size, in bits, of the blue component of the specified Metal pixel format. */
GLsizei mglMTLPixelFormatBitCountBlue(MTLPixelFormat pixelFormat);

/** Returns the size, in bits, of the alpha component of the specified Metal pixel format. */
GLsizei mglMTLPixelFormatBitCountAlpha(MTLPixelFormat pixelFormat);

/** Returns the size, in bits, of the depth component of the specified Metal pixel format. */
GLsizei mglMTLPixelFormatBitCountDepth(MTLPixelFormat pixelFormat);

/** Returns the size, in bits, of the stencil component of the specified Metal pixel format. */
GLsizei mglMTLPixelFormatBitCountStencil(MTLPixelFormat pixelFormat);



#pragma mark Textures

/**
 * This structure holds two MTLPixelFormat values, corresponding to a particular OpenGL
 * pixel format and type. In some cases, an exact match for a particular OpenGL format and
 * type cannot be found in Metal, and this structure allows for the definition of a couple
 * of Metal pixel format options.
 *
 * The uniformFormat element indicates the MTLPixelFormat with the same memory footprint 
 * as the corresponding OpenGL pixel format, but not necessarily containing the same RGBA
 * components. This format can be used when it is important to use the same memory layout 
 * for both the OpenGL and Metal texture formats (for example, to avoid copying content).
 *
 * Where there is no Metal pixel format with the same memory footprint as the corresponding
 * OpenGL pixel format and type (for example RGB), the uniformFormat element will contain
 * MTLPixelFormatInvalid.
 *
 * The swizzleFormat element indicates the MTLPixelFormat that contains the same components
 * as the corresponding OpenGL pixel format, but not necessarily in the same order or with 
 * the same memory footprint. This format can be used when it is important to access the
 * texture content using the correct components from within a Metal shader function.
 *
 * For the common case where an exact mapping exists between an OpenGL pixel format and 
 * type and the corresponding Metal pixel format, the swizzleFormat element will contain
 * MTLPixelFormatInvalid.
 */
typedef struct {
	MTLPixelFormat uniformFormat;
	MTLPixelFormat swizzleFormat;
} MGLMTLPixelFormatOptions;

/**
 * Returns the MTLPixelFormats that correspond to the specified combination of OpenGL pixel
 * format and pixel type.
 *
 * In some cases, an exact match for a particular OpenGL format and type cannot be found 
 * in Metal, and this function returns a structure containing a couple of mapping options.
 * See the notes for the MGLMTLPixelFormatOptions for more info regarding the returned options.
 *
 * If a match could not be determined, the returned structure will contain MTLPixelFormatInvalid 
 * in both elements in the returned structure.
 */
MGLMTLPixelFormatOptions mglMTLPixelFormatMapForOpenGLTexturePixelFormatAndType(GLenum pixelFormat,
																				GLenum pixelType);

/** Returns the OpenGL pixel format corresponding to the MTLPixelFormat. */
GLenum mglOpenGLPixelFormatFromMTLPixelFormat(MTLPixelFormat mtlPixFmt);

/** Returns the OpenGL pixel type corresponding to the MTLPixelFormat. */
GLenum mglOpenGLPixelTypeFromMTLPixelFormat(MTLPixelFormat mtlPixFmt);

/**
 * Copies the specified OpenGL pixels to the specified Metal pixels, taking into
 * consideration any structural differences in the respective pixel formats.
 *
 * This function does not convert between any two arbitrary OpenGL and Metal 
 * pixel formats. Conversion is restricted to those formats returned in the 
 * swizzleFormat element of the MGLMTLPixelFormatOptions structure returned 
 * by the mglMTLPixelFormatMapForOpenGLTexturePixelFormatAndType function, 
 * otherwise, the bytes of each OpenGL pixel are simply copied to the Metal pixel.
 */
void mglCopyOpenGLPixelsToMetalPixels(GLvoid* glPixels,
									  GLenum glPixelFormat,
									  GLenum glPixelType,
									  GLsizei glBytesPerRow,
									  GLsizei width,
									  GLsizei height,
									  GLvoid* mtlPixels,
									  MTLPixelFormat mtlPixelFormat,
									  GLsizei mtlBytesPerRow);

/**
 * Returns the Metal texture slice index matching the specified OpenGL texture face.
 *
 * Returns 0 if the slice index could not be determined.
 */
NSUInteger mglMTLTextureSliceFromGLTextureFace(GLenum face);

/**
 * Returns the MTLSamplerMipFilter value matching the specified OpenGL texture parameter.
 *
 * Returns MTLSamplerMipFilterNotMipmapped if the specified OpenGL texture paramete is not supported.
 */
MTLSamplerMipFilter mglMTLSamplerMipFilterFromGLTextureParameter(GLenum texParam);

/**
 * Returns the MTLSamplerMinMagFilter value matching the specified OpenGL texture parameter.
 *
 * Returns MTLSamplerMinMagFilterNearest if the specified OpenGL texture paramete is not supported.
 */
MTLSamplerMinMagFilter mglMTLSamplerMinMagFilterFromGLTextureParameter(GLenum texParam);

/**
 * Returns the MTLSamplerAddressMode value matching the specified OpenGL texture parameter.
 *
 * Returns MTLSamplerAddressModeClampToEdge if the specified OpenGL texture paramete is not supported.
 */
MTLSamplerAddressMode mglMTLSamplerAddressModeFromGLTextureParameter(GLenum texParam);

	
#pragma mark Renderbuffers

/**
 * Returns the MTLPixelFormat that matches the specified OpenGL renderbuffer format,
 * or returns MTLPixelFormatInvalid if a match could not be found.
 */
MTLPixelFormat mglMTLPixelFormatFromGLRenderbufferFormat(GLenum rbFormat);

/**
 * Returns the OpenGL renderbuffer format that matches the specified MTLPixelFormat,
 * or returns GL_NONE if a match could not be found.
 */
GLenum mglGLRenderbufferFormatFromMTLPixelFormat(MTLPixelFormat pixelFormat);

/** 
 * Returns the size of the specified component in the specified renderbuffer format. 
 */
GLsizei mglRenderbufferPixelComponentSize(GLenum rbFormat, GLenum component);
	
/**
 * Copies the specified Metal pixels to the specified OpenGL pixels, taking into
 * consideration any structural differences in the respective pixel formats.
 *
 * This function does not convert between any two arbitrary Metal and OpenGL pixel formats. 
 * Most Metal pixel formats are supported, but only the two OpenGL pixel formaat and type
 * combinations allowed by the glReadPixels() function are supported here:
 *   - GL_RGBA/GL_UNSIGNED_BYTE
 *   - GL_BGRA/GL_UNSIGNED_BYTE
 */
void mglCopyMetalPixelsToOpenGLPixels(GLvoid* mtlPixels,
									  MTLPixelFormat mtlPixelFormat,
									  GLsizei mtlBytesPerRow,
									  GLsizei width,
									  GLsizei height,
									  GLvoid* glPixels,
									  GLenum glPixelFormat,
									  GLenum glPixelType,
									  GLsizei glBytesPerRow);

#pragma mark Depth and stencil parameters

/** Returns the Metal comparison function that matches the specified OpenGL comparison function. */
MTLCompareFunction mglMTLCompareFunctionFromGLCompareFunction(GLenum compareFunc);

/** Returns the Metal stencil operation that matches the specified OpenGL stencil operation. */
MTLStencilOperation mglMTLStencilOperationFromGLStencilOperation(GLenum stencilOp);

	
#pragma mark Blending
	
/** Returns the Metal blending operation that matches the specified OpenGL blending equation. */
MTLBlendOperation mglMTLBlendOperationFromGLBlendEquation(GLenum blendMode);

/**
 * Returns the Metal blending function that matches the specified OpenGL blending function
 * when used as a source blending function.
 *
 * This function differs from the mglMTLBlendFactorFromGLDestinationBlendFactor only in the
 * validation checks performed on the input blendFunc.
 */
MTLBlendFactor mglMTLBlendFactorFromGLSourceBlendFactor(GLenum blendFunc);
	
/**
 * Returns the Metal blending function that matches the specified OpenGL blending function
 * when used as a destination blending function.
 *
 * This function differs from the mglMTLBlendFactorFromGLSourceBlendFactor only in the
 * validation checks performed on the input blendFunc.
 */
MTLBlendFactor mglMTLBlendFactorFromGLDestinationBlendFactor(GLenum blendFunc);
	
	
#pragma mark Vertex Attributes and Uniforms
	
/** Returns the Metal vertex format that matches the specified OpenGL vertex attribute characteristics. */
MTLVertexFormat mglMTLVertexFormatFromGLVertexTypeAndSize(GLenum type,
																	GLint size,
																	GLboolean normalized);
/**
 * Returns the OpenGL shader data type that matches the specified Metal MTLDataType.
 *
 * If the MTLDataType is of a type that is not an exact match for a valid OpenGL data type, 
 * but is equivalent to multiples of an OpenGL data type (for example, many of the
 * MTLDataType matrix formats, the smaller OpenGL data type is returned.
 */
GLenum mglGLShaderDataTypeFromMTLDataType(MTLDataType type);
	
/** Returns the OpenGL shader data type that matches the specified Metal MTLTextureType. */
GLenum mglGLShaderDataTypeFromMTLTextureType(MTLTextureType type);

/** Returns the number of component elements in the specified OpenGL data type. */
GLsizei mglGLDataTypeElementCount(GLenum type);

/** Returns the size, in bytes, of the specified OpenGL data type. */
size_t mglGLDataTypeSize(GLenum type);

/** Returns the size, in bytes, of the specified Metal data type. */
size_t mglMTLDataTypeSize(MTLDataType type);

	
#pragma mark Drawing

/**
 * Returns the MTLPrimitiveType that matches the specified OpenGL drawing mode,
 * or returns MTLPrimitiveTypeTriangle if a match could not be found.
 */
MTLPrimitiveType mglMTLPrimitiveTypeFromGLPrimitiveType(GLenum primType);

#ifdef __cplusplus
}
#endif	//  __cplusplus
