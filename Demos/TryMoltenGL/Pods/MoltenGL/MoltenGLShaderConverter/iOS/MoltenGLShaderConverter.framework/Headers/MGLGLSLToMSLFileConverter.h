/*
 * MGLGLSLToMSLFileConverter.h
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


#import "MGLGLSLToMSLConverter.h"
#import "MGLDirectoryProcessor.h"


#pragma mark -
#pragma mark MGLGLObject protocol

/** Defines the interface behaviour for objects that keep track of the file extensions of GLSL shader files. */
MLN_PUBLIC_SYMBOL @protocol MGLGLSLFileExtensionTracker <NSObject>

/**
 * Indicates whether both the GLSL and Metal source code should be written to the output file.
 *
 * If this property is set to YES, both the input GLSL source code, and the converted Metal
 * source code will be written to the output file. The GLSL source code is written first,
 * and then the converted Metal source code is appended. The Metal source code is separated
 * from the GLSL code with a line containing the following pragma delimiter:
 *
 *   - #pragma MoltenGL language Metal
 *
 * If this property is set to NO, only the converted Metal source code will be written to the
 * output file, and no pragma delimiter is written.
 *
 * The initial value of this property is NO.
 */
@property(nonatomic, assign) BOOL shouldCombineSourceCode;

/**
 * Returns a list of file extensions that indicate that a file contains GLSL shader source
 * code for a vertex shader.
 */
@property(nonatomic, readonly) NSSet* vertexShaderFileExtensions;

/** Adds the specified file extension to the collection of file extensions in the vertexShaderFileExtensions property. */
-(void) addVertexShaderFileExtension: (NSString*) fileExtn;

/**
 * Returns a list of file extensions that indicate that a file contains GLSL shader source
 * code for a fragment shader.
 */
@property(nonatomic, readonly) NSSet* fragmentShaderFileExtensions;

/** Adds the specified file extension to the collection of file extensions in the fragmentShaderFileExtensions property. */
-(void) addFragmentShaderFileExtension: (NSString*) fileExtn;

@end


#pragma mark -
#pragma mark MGLGLSLToMSLFileConverter

/**
 * Reads OpenGL Shading Language (GLSL) source code contained in a file, converts it to
 * Metal Shading Language source code, and writes the Metal source code to a file.
 *
 * Use the convertGLSLSourceFile:toMetalSourceFile:forShaderType:withFunctionName: method
 * to convert GLSL source code in a GLSL file to Metal source code in a Metal file.
 * 
 * This conversion method can be invoked repeatedly, with different GLSL source files.
 * To convert multiple GLSL shader files, you can instantiate a single instance of this
 * class, and then invoke the conversion method once for each GLSL shader file.
 */
MLN_PUBLIC_SYMBOL @interface MGLGLSLToMSLFileConverter : MGLGLSLToMSLConverter <MGLGLSLFileExtensionTracker>


#pragma mark Converting GLSL to Metal SL

/**
 * Converts the OpenGL GLSL shader source code in the specified GLSL file, containing the source
 * code for a single GLSL shader, into the source code for a single Metal shader function with 
 * the specified function name, saves that Metal shader source code to the specified Metal file,
 * and returns whether or not the conversion was successful.
 *
 * This method converts a single GLSL shader into a single Metal shader function.
 *
 * The glslFilePath parameter indicates the path to the file containing the GLSL source code that
 * is to be converted. This path may be either absolute, or relative to the app's working directory.
 *
 * The glslVersion parameter indicates the GLSL version to use when parsing the GLSL source code,
 * if the GLSL version is not already identified in the GLSL source code itself via the #version
 * directive. This parameter may be set to kMGLGLSLVersionAuto to automatically select the latest
 * supported GLSL version for the platform on which this method is run. If the GLSL source code
 * already identifies the GLSL version, the glslVersion parameter is ignored.
 *
 * The shaderType parameter indicates the type of OpenGL shader, and should be one of
 * GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, or GL_NONE. If the parameter is GL_NONE, the shader
 * type will be determined from the file extension of the specified GLSL shader file, by
 * comparing the file extension against the list of file extensions in the
 * vertexShaderFileExtensions and fragmentShaderFileExtensions properties of this instance.
 * For example, a GLSL file with the name MyShader.vsh would be considered to contain GLSL
 * source code for a vertex shader, unless the shaderType parameter indicates otherwise.
 *
 * The mtlFuncName parameter indicates the name that should be assigned to the Metal shader
 * function created from the GLSL source code. If this parameter is nil, the function name 
 * will be derived from the name and extension of the specified GLSL file. For example, the 
 * Metal function name derived from a GLSL file named MyShader.vsh would be MyShader_vsh.
 *
 * The mtlFilePath parameter indicates the path to the file to which the converted Metal
 * source code is to be written. This path may be either absolute, or relative to the app's
 * working directory, or it may be nil.
 *
 * If the mtlFilePath parameter is nil, and the shouldCombineSourceCode property is set to YES,
 * the converted Metal source code will be appended to the end of the file containing the GLSL
 * source code. The Metal source code is separated from the GLSL code with a line containing
 * the following pragma delimiter:
 *
 *   - #pragma MoltenGL language Metal
 *
 * If the mtlFilePath parameter is nil, and the shouldCombineSourceCode property is set to NO, 
 * the path to the Metal file will be derived from the name and extension of the specified GLSL
 * file, and the Metal file will be located in the same directory as the GLSL file. For example,
 * if the path to the GLSL file is SomePath/MyShader.vsh, and the mtlFilePath parameter is nil,
 * the converted Metal source code will be saved to the file SomePath/MyShader_vsh.metal.
 *
 * If the Metal source code file already exists, its contents will be overwritten.
 *
 * If the conversion is successful, this method will return YES. If the conversion is 
 * unsuccessful, nothing will be written to the Metal file, and this method will return NO.
 * A description of the failure reason can be retrieved from the infoLog property.
 *
 * The GLSL file may also contain Metal Shading Language source code that is separated from
 * the GLSL code by a line containing the following pragma delimiter:
 *
 *   - #pragma MoltenGL language Metal
 *
 * This Metal Shading Language source code will be ignored.
 *
 * Reading the GLSL file supports the use of #import directive statements within the GLSL 
 * files, to allow a shader to be assembled from modules from multiple nested files.
 *
 * This method can be invoked repeatedly, with different GLSL source files. To convert 
 * multiple GLSL shader files, you can instantiate a single instance of this class, and
 * then invoke this method once for each GLSL shader file.
 */
-(BOOL) convertGLSLSourceFile: (NSString*) glslFilePath
			  withGLSLVersion: (MGLGLSLVersion) glslVersion
				forShaderType: (GLenum) shaderType
		 toMetalFunctionNamed: (NSString*) mtlFuncName
			inMetalSourceFile: (NSString*) mtlFilePath;

/**
 * Returns a list of file extensions that indicate that a file contains GLSL shader source
 * code for a vertex shader.
 *
 * This list is used by the convertGLSLSourceFile:toMetalSourceFile:forShaderType:withFunctionName:
 * method when the shader type is not explictly indicated, to determine whether the GLSL file
 * contains GLSL source code for a vertex shader.
 */
@property(nonatomic, readonly) NSSet* vertexShaderFileExtensions;

/** Adds the specified file extension to the collection of file extensions in the vertexShaderFileExtensions property. */
-(void) addVertexShaderFileExtension: (NSString*) fileExtn;

/**
 * Returns a list of file extensions that indicate that a file contains GLSL shader source
 * code for a fragment shader.
 *
 * This list is used by the convertGLSLSourceFile:toMetalSourceFile:forShaderType:withFunctionName:
 * method when the shader type is not explictly indicated, to determine whether the GLSL file
 * contains GLSL source code for a fragment shader.
 */
@property(nonatomic, readonly) NSSet* fragmentShaderFileExtensions;

/** Adds the specified file extension to the collection of file extensions in the fragmentShaderFileExtensions property. */
-(void) addFragmentShaderFileExtension: (NSString*) fileExtn;

@end


#pragma mark -
#pragma mark MGLGLSLToMSLDirectoryProcessor

/**
 * An MGLDirectoryProcessor that converts files containing vertex and/or fragment shader source
 * code in GLSL format to files containing the equivalent shader source code in Metal format.
 */
MLN_PUBLIC_SYMBOL @interface MGLGLSLToMSLDirectoryProcessor : MGLDirectoryProcessor <MGLGLSLFileExtensionTracker>

/** 
 * Indicates the version of GLSL to used when parsing the GLSL files. 
 *
 * The initial value of this property is kMGLGLSLVersionAuto.
 */
@property(nonatomic, assign) MGLGLSLVersion glslVersion;

/** 
 * Indicates the type of shaders to convert.
 *
 * This property should be set to either GL_VERTEX_SHADER to process only vertex shader files,
 * GL_FRAGMENT_SHADER to process only fragment shader files, or GL_NONE to process both types
 * of shader files.
 *
 * The initial value of this property is GL_NONE.
 */
@property(nonatomic, assign) GLenum shaderType;

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
@property(nonatomic, assign, assign) BOOL shouldInvertTexCoordYAxis;

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
 * Adds the specified file extension to the collection of file extensions in the vertexShaderFileExtensions
 * property, and to the collection  of allowed file extensions in the allowedFileExtensions property.
 */
-(void) addVertexShaderFileExtension: (NSString*) fileExtn;

/**
 * Adds the specified file extension to the collection of file extensions in the fragmentShaderFileExtensions
 * property, and to the collection  of allowed file extensions in the allowedFileExtensions property.
 */
-(void) addFragmentShaderFileExtension: (NSString*) fileExtn;

@end
