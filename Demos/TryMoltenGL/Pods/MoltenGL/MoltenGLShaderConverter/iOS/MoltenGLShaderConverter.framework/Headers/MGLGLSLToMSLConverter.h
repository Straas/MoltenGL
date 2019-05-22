/*
 * MGLGLSLToMSLConverter.h
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


#import "mglEnv.h"
#import <Foundation/Foundation.h>

#ifdef __MAC_OS_X_VERSION_MAX_ALLOWED
#import <OpenGL/gltypes.h>
#endif
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#import <OpenGLES/gltypes.h>
#endif

// Define the few GL enums that we need, to avoid conflicts when using OpenGL ES on macOS.
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_GEOMETRY_SHADER                0x8DD9
#define GL_GEOMETRY_SHADER_ARB            0x8DD9
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_NONE                           0


#pragma mark Enumerations

/** Enumeration of supported OpenGL GLSL versions. */
typedef enum {
	kMGLGLSLVersionAuto,			/**< GLSL version set to latest version for expected platform. */
	kMGLGLSLVersion100ES,			/**< GLSL ES version 1.00. */
	kMGLGLSLVersion300ES,			/**< GLSL ES version 3.00. */
	kMGLGLSLVersion110,				/**< GLSL version 1.10. */
	kMGLGLSLVersion120,				/**< GLSL version 1.20. */
} MGLGLSLVersion;

/** Returns the GLSL version string corresponding to the specified GLSL version. */
MLN_PUBLIC_SYMBOL NSString* NSStringFromMGLGLSLVersion(MGLGLSLVersion glslVersion);


#pragma mark -
#pragma mark MGLGLSLToMSLConverter

/** 
 * Converts OpenGL Shading Language (GLSL) source code to Metal Shading Language source code.
 *
 * Use the convertGLSLSource:withGLSLVersion:forShaderType:toMetalFunctionNamed: method
 * to convert GLSL source code to Metal source code, then retrieve the Metal source code
 * from the mslSourceCode property.
 * 
 * The conversion methods can be invoked repeatedly, with different GLSL source strings. 
 * To convert multiple GLSL shaders, you can instantiate a single instance of this class, 
 * and then invoke one of the conversion methods once for each shader.
 */
MLN_PUBLIC_SYMBOL @interface MGLGLSLToMSLConverter : NSObject

/**
 * Indicates whether the Y-axis of texture samplers should be inverted.
 *
 * The texture coordinate system of Metal is inverted, relative to that of OpenGL.
 * In order to align textures that have been developed for OpenGL, this property can be
 * set to YES to cause the samplers of Metal shaders to invert the Y axis when sampling.
 *
 * Changing the value of this property affects the results of subsequent conversions.
 *
 * The initial value of this property is YES.
 */
@property(nonatomic, assign) BOOL shouldInvertTexCoordYAxis;

/**
 * Indicates whether the GLSL and MSL shader source code should be logged to the console,
 * to aid in troubleshooting.
 *
 * Changing the value of this property affects the behaviour of subsequent conversions.
 *
 * The initial value of this property is NO.
 */
@property(nonatomic, assign) BOOL shouldLogSourceCode;

/**
 * Converts the specified OpenGL GLSL shader source string, comprising the source code for 
 * a single GLSL shader, into the source code for a single Metal shader function with the
 * specified name, and returns whether the conversion was successful.
 *
 * This method converts a single GLSL shader into a single Metal shader function.
 *
 * The glslVersion parameter indicates the GLSL version to use when parsing the GLSL source code,
 * if the GLSL version is not already identified in the GLSL source code itself via the #version
 * directive. This parameter may be set to kMGLGLSLVersionAuto to automatically select the latest
 * supported GLSL version for the platform on which this method is run. If the GLSL source code
 * already identifies the GLSL version, the glslVersion parameter is ignored.
 *
 * The shaderType parameter indicates the type of OpenGL shader, and must be either
 * GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
 *
 * The mtlFuncName parameter indicates the name that should be assigned to the Metal shader
 * function. If this method is nil, a function name will be automatically generated. Each
 * generated function name will be unique over the lifetime of this instance. Be aware that
 * Metal requires that each MTLFunction in a single MTLLibrary must have a unique name.
 * Regardless of whether the function name is supplied or generated, after conversion, the
 * Metal function name can be retrieved from the mtlFunctionName property.
 *
 * If the conversion is successful, the converted Metal source code can be retrieved from
 * the mslSourceCode property. If the conversion is unsuccessful, the mslSourceCode property
 * will be nil, and a description of the failure reason can be retrieved from the infoLog
 * property. After conversion, the GLSL source code can be retrieved from the glslSourceCode
 * property, regardless of whether the conversion was successful or not.
 *
 * This method can be invoked repeatedly, with different GLSL source strings. To convert
 * multiple GLSL shaders, you can instantiate a single instance of this class, and then
 * invoke this method once for each shader.
 */
-(BOOL) convertGLSLSource: (NSString*) glslSourceStr
		  withGLSLVersion: (MGLGLSLVersion) glslVersion
			forShaderType: (GLenum) shaderType
	 toMetalFunctionNamed: (NSString*) mtlFuncName;

/**
 * Returns whether the most recent conversion was successful.
 *
 * The initial value of this property is NO. It is set to YES upon successful conversion.
 */
@property(nonatomic, assign, readonly) BOOL wasConverted;

/**
 * Returns the original GLSL source code that was submitted to the most recent conversion,
 * or nil if no conversion was attempted.
 */
@property(nonatomic, retain, readonly) NSString* glslSourceCode;

/** 
 * Returns the Metal source code resulting from the most recent conversion,
 * or nil if the conversion was unsuccessful.
 */
@property(nonatomic, retain, readonly) NSString* mslSourceCode;

/**
 * Returns the name of the Metal function from the most recent conversion, 
 * or nil if no conversion was attempted.
 *
 * The function name can either be provided to the conversion method, or can be 
 * automatically generated. See the notes for the conversion methods for more info.
 */
@property(nonatomic, retain, readonly) NSString* mtlFunctionName;

/** Returns the info log of the most recent conversion. */
@property(nonatomic, retain, readonly) NSString* infoLog;

/** Returns the number of conversions that have been processed by this instance. */
@property(nonatomic, assign, readonly) NSUInteger conversionCount;


#pragma mark Allocation and initialization

/** Returns a new autoreleased instance. */
+(instancetype) converter;

@end


#pragma mark -
#pragma mark NSMutableString extensions

@interface NSMutableString (MGLShaderConverter)

/**
 * If the specified source does not already contain a #version directive,
 * prepends a #version directive corresponding to the specified GLSL version.
 */
-(void) ensureGLSLVersion: (MGLGLSLVersion) glslVersion;

@end
