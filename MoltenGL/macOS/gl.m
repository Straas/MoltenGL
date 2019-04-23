/*
 * gl.m
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
 * This file provides an empty stub implementation of the OpenGL ES 2 for use with macOS.
 *
 * When using MoltenGL on macOS on a machine that does not support Metal, or if you have 
 * chosen not to use Metal (by setting the build setting MGL_SUPPORT_OPENGL_ON_METAL=0), 
 * your OpenGL ES app needs to be able to access a "native" OpenGL ES engine. macOS supports
 * OpenGL by default, and so an OpenGL ES implementation must be provided for use on macOS.
 *
 * To allow your app to compile, under macOS, add this source code file to your macOS app project. 
 * Do not add this file to an iOS app, as iOS already provides a native OpenGL ES engine.
 *
 * This file represents the OpenGL ES 2 behaviour required by MoltenGL when not using Metal,
 * but this default implementation does nothing. If your app requires OpenGL ES 2 
 * functionality on macOS when not running Metal, you can add it here, or acquire a third-party
 * OpenGL ES implementation for macOS, and link it instead of compiling and linking to this file.
 *
 * You can download a free public OpenGL ES 2 implementation for macOS from https://moltengl.com/downloads/#ogles-osx
 * Remove this file from your app project, add the downloaded libGLESv2.dylib dynamic 
 * library file to your app target, and in the Build Phases panel, add it to the
 * "Link Binary With Libraries" AND "Copy Files" lists.
 */

#import <MoltenGL/mglEnv.h>

#if MLN_MACOS

#import <OpenGLES/gltypes.h>
#import <Foundation/Foundation.h>

static inline void MGLUnimplementedOGLES(NSString* funcName) { NSLog(@"OpenGL ES 2 function %@() is not implemented under macOS.", funcName); }

void glActiveTexture(GLenum texture)  {
	MGLUnimplementedOGLES(@"glActiveTexture");
}

void glAttachShader(GLuint program, GLuint shader)  {
	MGLUnimplementedOGLES(@"glAttachShader");
}

void glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)  {
	MGLUnimplementedOGLES(@"glBindAttribLocation");
}

void glBindBuffer(GLenum target, GLuint buffer)  {
	MGLUnimplementedOGLES(@"glBindBuffer");
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)  {
	MGLUnimplementedOGLES(@"glBindFramebuffer");
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)  {
	MGLUnimplementedOGLES(@"glBindRenderbuffer");
}

void glBindTexture(GLenum target, GLuint texture)  {
	MGLUnimplementedOGLES(@"glBindTexture");
}

void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)  {
	MGLUnimplementedOGLES(@"glBlendColor");
}

void glBlendEquation(GLenum mode)  {
	MGLUnimplementedOGLES(@"glBlendEquation");
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)  {
	MGLUnimplementedOGLES(@"glBlendEquationSeparate");
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)  {
	MGLUnimplementedOGLES(@"glBlendFunc");
}

void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)  {
	MGLUnimplementedOGLES(@"glBlendFuncSeparate");
}

void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)  {
	MGLUnimplementedOGLES(@"glBufferData");
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)  {
	MGLUnimplementedOGLES(@"glBufferSubData");
}

GLenum glCheckFramebufferStatus(GLenum target)  {
	MGLUnimplementedOGLES(@"glCheckFramebufferStatus");
	return 0;
}

void glClear(GLbitfield mask)  {
	MGLUnimplementedOGLES(@"glClear");
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)  {
	MGLUnimplementedOGLES(@"glClearColor");
}

void glClearDepthf(GLclampf depth)  {
	MGLUnimplementedOGLES(@"glClearDepthf");
}

void glClearStencil(GLint s)  {
	MGLUnimplementedOGLES(@"glClearStencil");
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)  {
	MGLUnimplementedOGLES(@"glColorMask");
}

void glCompileShader(GLuint shader)  {
	MGLUnimplementedOGLES(@"glCompileShader");
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)  {
	MGLUnimplementedOGLES(@"glCompressedTexImage2D");
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)  {
	MGLUnimplementedOGLES(@"glCompressedTexSubImage2D");
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)  {
	MGLUnimplementedOGLES(@"glCopyTexImage2D");
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)  {
	MGLUnimplementedOGLES(@"glCopyTexSubImage2D");
}

GLuint glCreateProgram(void)  {
	MGLUnimplementedOGLES(@"glCreateProgram");
	return 0;
}

GLuint glCreateShader(GLenum type)  {
	MGLUnimplementedOGLES(@"glCreateShader");
	return 0;
}

void glCullFace(GLenum mode)  {
	MGLUnimplementedOGLES(@"glCullFace");
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)  {
	MGLUnimplementedOGLES(@"glDeleteBuffers");
}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)  {
	MGLUnimplementedOGLES(@"glDeleteFramebuffers");
}

void glDeleteProgram(GLuint program)  {
	MGLUnimplementedOGLES(@"glDeleteProgram");
}

void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)  {
	MGLUnimplementedOGLES(@"glDeleteProgram");
}

void glDeleteShader(GLuint shader)  {
	MGLUnimplementedOGLES(@"glDeleteShader");
}

void glDeleteTextures(GLsizei n, const GLuint* textures)  {
	MGLUnimplementedOGLES(@"glDeleteTextures");
}

void glDepthFunc(GLenum func)  {
	MGLUnimplementedOGLES(@"glDepthFunc");
}

void glDepthMask(GLboolean flag)  {
	MGLUnimplementedOGLES(@"glDepthMask");
}

void glDepthRangef(GLclampf zNear, GLclampf zFar)  {
	MGLUnimplementedOGLES(@"glDepthRangef");
}

void glDetachShader(GLuint program, GLuint shader)  {
	MGLUnimplementedOGLES(@"glDetachShader");
}

void glDisable(GLenum cap)  {
	MGLUnimplementedOGLES(@"glDisable");
}

void glDisableVertexAttribArray(GLuint index)  {
	MGLUnimplementedOGLES(@"glDisableVertexAttribArray");
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)  {
	MGLUnimplementedOGLES(@"glDrawArrays");
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)  {
	MGLUnimplementedOGLES(@"glDrawElements");
}

void glEnable(GLenum cap)  {
	MGLUnimplementedOGLES(@"glEnable");
}

void glEnableVertexAttribArray(GLuint index)  {
	MGLUnimplementedOGLES(@"glEnableVertexAttribArray");
}

void glFinish(void)  {
	MGLUnimplementedOGLES(@"glFinish");
}

void glFlush(void)  {
	MGLUnimplementedOGLES(@"glFlush");
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)  {
	MGLUnimplementedOGLES(@"glFramebufferRenderbuffer");
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)  {
	MGLUnimplementedOGLES(@"glFramebufferTexture2D");
}

void glFrontFace(GLenum mode)  {
	MGLUnimplementedOGLES(@"glFrontFace");
}

void glGenBuffers(GLsizei n, GLuint* buffers)  {
	MGLUnimplementedOGLES(@"glGenBuffers");
}

void glGenerateMipmap(GLenum target)  {
	MGLUnimplementedOGLES(@"glGenerateMipmap");
}

void glGenFramebuffers(GLsizei n, GLuint* framebuffers)  {
	MGLUnimplementedOGLES(@"glGenFramebuffers");
}

void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)  {
	MGLUnimplementedOGLES(@"glGenRenderbuffers");
}

void glGenTextures(GLsizei n, GLuint* textures)  {
	MGLUnimplementedOGLES(@"glGenTextures");
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)  {
	MGLUnimplementedOGLES(@"glGetActiveAttrib");
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)  {
	MGLUnimplementedOGLES(@"glGetActiveUniform");
}

void glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)  {
	MGLUnimplementedOGLES(@"glGetAttachedShaders");
}

int glGetAttribLocation(GLuint program, const GLchar* name)  {
	MGLUnimplementedOGLES(@"glGetAttribLocation");
	return 0;
}

void glGetBooleanv(GLenum pname, GLboolean* params)  {
	MGLUnimplementedOGLES(@"glGetBooleanv");
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetBufferParameteriv");
}

GLenum glGetError(void)  {
	MGLUnimplementedOGLES(@"glGetError");
	return 0;
}

void glGetFloatv(GLenum pname, GLfloat* params)  {
	MGLUnimplementedOGLES(@"glGetFloatv");
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetFramebufferAttachmentParameteriv");
}

void glGetIntegerv(GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetIntegerv");
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetProgramiv");
}

void glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)  {
	MGLUnimplementedOGLES(@"glGetProgramInfoLog");
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetRenderbufferParameteriv");
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetShaderiv");
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)  {
	MGLUnimplementedOGLES(@"glGetShaderInfoLog");
}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)  {
	MGLUnimplementedOGLES(@"glGetShaderPrecisionFormat");
}

void glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)  {
	MGLUnimplementedOGLES(@"glGetShaderSource");
}

const GLubyte* glGetString(GLenum name)  {
	MGLUnimplementedOGLES(@"glGetString");
	return NULL;
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)  {
	MGLUnimplementedOGLES(@"glGetTexParameterfv");
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetTexParameteriv");
}

void glGetUniformfv(GLuint program, GLint location, GLfloat* params)  {
	MGLUnimplementedOGLES(@"glGetUniformfv");
}

void glGetUniformiv(GLuint program, GLint location, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetUniformiv");
}

int glGetUniformLocation(GLuint program, const GLchar* name)  {
	MGLUnimplementedOGLES(@"glGetUniformLocation");
	return 0;
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)  {
	MGLUnimplementedOGLES(@"glGetVertexAttribfv");
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)  {
	MGLUnimplementedOGLES(@"glGetVertexAttribiv");
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)  {
	MGLUnimplementedOGLES(@"glGetVertexAttribPointerv");
}

void glHint(GLenum target, GLenum mode)  {
	MGLUnimplementedOGLES(@"glHint");
}

GLboolean glIsBuffer(GLuint buffer)  {
	MGLUnimplementedOGLES(@"glIsBuffer");
	return false;
}

GLboolean glIsEnabled(GLenum cap)  {
	MGLUnimplementedOGLES(@"glIsEnabled");
	return false;
}

GLboolean glIsFramebuffer(GLuint framebuffer)  {
	MGLUnimplementedOGLES(@"glIsFramebuffer");
	return false;
}

GLboolean glIsProgram(GLuint program)  {
	MGLUnimplementedOGLES(@"glIsProgram");
	return false;
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)  {
	MGLUnimplementedOGLES(@"glIsRenderbuffer");
	return false;
}

GLboolean glIsShader(GLuint shader)  {
	MGLUnimplementedOGLES(@"glIsShader");
	return false;
}

GLboolean glIsTexture(GLuint texture)  {
	MGLUnimplementedOGLES(@"glIsTexture");
	return false;
}

void glLineWidth(GLfloat width)  {
	MGLUnimplementedOGLES(@"glLineWidth");
}

void glLinkProgram(GLuint program)  {
	MGLUnimplementedOGLES(@"glLinkProgram");
}

void glPixelStorei(GLenum pname, GLint param)  {
	MGLUnimplementedOGLES(@"glPixelStorei");
}

void glPolygonOffset(GLfloat factor, GLfloat units)  {
	MGLUnimplementedOGLES(@"glPolygonOffset");
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)  {
	MGLUnimplementedOGLES(@"glReadPixels");
}

void glReleaseShaderCompiler(void)  {
	MGLUnimplementedOGLES(@"glReleaseShaderCompiler");
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)  {
	MGLUnimplementedOGLES(@"glRenderbufferStorage");
}

void glSampleCoverage(GLclampf value, GLboolean invert)  {
	MGLUnimplementedOGLES(@"glSampleCoverage");
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)  {
	MGLUnimplementedOGLES(@"glScissor");
}

void glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)  {
	MGLUnimplementedOGLES(@"glShaderBinary");
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)  {
	MGLUnimplementedOGLES(@"glShaderSource");
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)  {
	MGLUnimplementedOGLES(@"glStencilFunc");
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)  {
	MGLUnimplementedOGLES(@"glStencilFuncSeparate");
}

void glStencilMask(GLuint mask)  {
	MGLUnimplementedOGLES(@"glStencilMask");
}

void glStencilMaskSeparate(GLenum face, GLuint mask)  {
	MGLUnimplementedOGLES(@"glStencilMaskSeparate");
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)  {
	MGLUnimplementedOGLES(@"glStencilOp");
}

void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)  {
	MGLUnimplementedOGLES(@"glStencilOpSeparate");
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)  {
	MGLUnimplementedOGLES(@"glTexImage2D");
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)  {
	MGLUnimplementedOGLES(@"glTexParameterf");
}

void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)  {
	MGLUnimplementedOGLES(@"glTexParameterfv");
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)  {
	MGLUnimplementedOGLES(@"glTexParameteri");
}

void glTexParameteriv(GLenum target, GLenum pname, const GLint* params)  {
	MGLUnimplementedOGLES(@"glTexParameteriv");
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)  {
	MGLUnimplementedOGLES(@"glTexSubImage2D");
}

void glUniform1f(GLint location, GLfloat x)  {
	MGLUnimplementedOGLES(@"glUniform1f");
}

void glUniform1fv(GLint location, GLsizei count, const GLfloat* v)  {
	MGLUnimplementedOGLES(@"glUniform1fv");
}

void glUniform1i(GLint location, GLint x)  {
	MGLUnimplementedOGLES(@"glUniform1i");
}

void glUniform1iv(GLint location, GLsizei count, const GLint* v)  {
	MGLUnimplementedOGLES(@"glUniform1iv");
}

void glUniform2f(GLint location, GLfloat x, GLfloat y)  {
	MGLUnimplementedOGLES(@"glUniform2f");
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* v)  {
	MGLUnimplementedOGLES(@"glUniform2fv");
}

void glUniform2i(GLint location, GLint x, GLint y)  {
	MGLUnimplementedOGLES(@"glUniform2i");
}

void glUniform2iv(GLint location, GLsizei count, const GLint* v)  {
	MGLUnimplementedOGLES(@"glUniform2iv");
}

void glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)  {
	MGLUnimplementedOGLES(@"glUniform3f");
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* v)  {
	MGLUnimplementedOGLES(@"glUniform3fv");
}

void glUniform3i(GLint location, GLint x, GLint y, GLint z)  {
	MGLUnimplementedOGLES(@"glUniform3i");
}

void glUniform3iv(GLint location, GLsizei count, const GLint* v)  {
	MGLUnimplementedOGLES(@"glUniform3iv");
}

void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)  {
	MGLUnimplementedOGLES(@"glUniform4f");
}

void glUniform4fv(GLint location, GLsizei count, const GLfloat* v)  {
	MGLUnimplementedOGLES(@"glUniform4fv");
}

void glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)  {
	MGLUnimplementedOGLES(@"glUniform4i");
}

void glUniform4iv(GLint location, GLsizei count, const GLint* v)  {
	MGLUnimplementedOGLES(@"glUniform4iv");
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)  {
	MGLUnimplementedOGLES(@"glUniformMatrix2fv");
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)  {
	MGLUnimplementedOGLES(@"glUniformMatrix3fv");
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)  {
	MGLUnimplementedOGLES(@"glUniformMatrix4fv");
}

void glUseProgram(GLuint program)  {
	MGLUnimplementedOGLES(@"glUseProgram");
}

void glValidateProgram(GLuint program)  {
	MGLUnimplementedOGLES(@"glValidateProgram");
}

void glVertexAttrib1f(GLuint indx, GLfloat x)  {
	MGLUnimplementedOGLES(@"glVertexAttrib1f");
}

void glVertexAttrib1fv(GLuint indx, const GLfloat* values)  {
	MGLUnimplementedOGLES(@"glVertexAttrib1fv");
}

void glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)  {
	MGLUnimplementedOGLES(@"glVertexAttrib2f");
}

void glVertexAttrib2fv(GLuint indx, const GLfloat* values)  {
	MGLUnimplementedOGLES(@"glVertexAttrib2fv");
}

void glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)  {
	MGLUnimplementedOGLES(@"glVertexAttrib3f");
}

void glVertexAttrib3fv(GLuint indx, const GLfloat* values)  {
	MGLUnimplementedOGLES(@"glVertexAttrib3fv");
}

void glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)  {
	MGLUnimplementedOGLES(@"glVertexAttrib4f");
}

void glVertexAttrib4fv(GLuint indx, const GLfloat* values)  {
	MGLUnimplementedOGLES(@"glVertexAttrib4fv");
}

void glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)  {
	MGLUnimplementedOGLES(@"glVertexAttribPointer");
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)  {
	MGLUnimplementedOGLES(@"glViewport");
}

#endif	// MLN_MACOS
