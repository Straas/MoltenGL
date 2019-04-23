/*
 * glext.m
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
 * This file provides an empty stub implementation of the OpenGL ES 2 extensions for use with macOS.
 *
 * When using MoltenGL on macOS on a machine that does not support Metal, or if you have
 * chosen not to use Metal (by setting the build setting MGL_SUPPORT_OPENGL_ON_METAL=0),
 * your OpenGL ES app needs to be able to access a "native" OpenGL ES engine. macOS supports
 * OpenGL by default, and so an OpenGL ES implementation must be provided for use on macOS.
 *
 * To allow your app to compile, under macOS, add this source code file to your macOS app project.
 * Do not add this file to an iOS app, as iOS already provides a native OpenGL ES engine.
 *
 * This file represents the OpenGL ES 2 extension behaviour required by MoltenGL when not using Metal,
 * but this default implementation does nothing. If your app requires OpenGL ES 2 extension
 * functionality on macOS when not running Metal, you can add it here.
 */

#import <MoltenGL/mglEnv.h>

#if MLN_MACOS

#import <OpenGLES/gltypes.h>
#import <Foundation/Foundation.h>

static inline void MGLUnimplementedOGLES(NSString* funcName) { NSLog(@"OpenGL ES 2 extension function %@() is not implemented under macOS.", funcName); }

GLvoid glCopyTextureLevelsAPPLE(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) {
	MGLUnimplementedOGLES(@"glCopyTextureLevelsAPPLE");
}

GLvoid glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
	MGLUnimplementedOGLES(@"glRenderbufferStorageMultisampleAPPLE");
}

GLvoid glResolveMultisampleFramebufferAPPLE(void) {
	MGLUnimplementedOGLES(@"glResolveMultisampleFramebufferAPPLE");
}

GLsync glFenceSyncAPPLE(GLenum condition, GLbitfield flags) {
	MGLUnimplementedOGLES(@"glFenceSyncAPPLE");
	return NULL;
}

GLboolean glIsSyncAPPLE(GLsync sync) {
	MGLUnimplementedOGLES(@"glIsSyncAPPLE");
	return false;
}

void glDeleteSyncAPPLE(GLsync sync) {
	MGLUnimplementedOGLES(@"glDeleteSyncAPPLE");
}

GLenum glClientWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout) {
	MGLUnimplementedOGLES(@"glClientWaitSyncAPPLE");
	return 0;
}

void glWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout) {
	MGLUnimplementedOGLES(@"glWaitSyncAPPLE");
}

void glGetInteger64vAPPLE(GLenum pname, GLint64* params) {
	MGLUnimplementedOGLES(@"glGetInteger64vAPPLE");
}

void glGetSyncivAPPLE(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) {
	MGLUnimplementedOGLES(@"glGetSyncivAPPLE");
}

GLvoid glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar* label) {
	MGLUnimplementedOGLES(@"glLabelObjectEXT");
}

GLvoid glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei* length, GLchar* label) {
	MGLUnimplementedOGLES(@"glGetObjectLabelEXT");
}

GLvoid glInsertEventMarkerEXT(GLsizei length, const GLchar* marker) {
	MGLUnimplementedOGLES(@"glInsertEventMarkerEXT");
}

GLvoid glPushGroupMarkerEXT(GLsizei length, const GLchar* marker) {
	MGLUnimplementedOGLES(@"glPushGroupMarkerEXT");
}

GLvoid glPopGroupMarkerEXT(void) {
	MGLUnimplementedOGLES(@"glPopGroupMarkerEXT");
}

GLvoid glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum* attachments) {
	MGLUnimplementedOGLES(@"glDiscardFramebufferEXT");
}

GLvoid glDrawArraysInstancedEXT(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount) {
	MGLUnimplementedOGLES(@"glDrawArraysInstancedEXT");
}

GLvoid glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instanceCount) {
	MGLUnimplementedOGLES(@"glDrawElementsInstancedEXT");
}

GLvoid glVertexAttribDivisorEXT(GLuint index, GLuint divisor) {
	MGLUnimplementedOGLES(@"glVertexAttribDivisorEXT");
}

GLvoid* glMapBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
	MGLUnimplementedOGLES(@"glMapBufferRangeEXT");
	return NULL;
}

GLvoid glFlushMappedBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length) {
	MGLUnimplementedOGLES(@"glFlushMappedBufferRangeEXT");
}

GLvoid glGenQueriesEXT(GLsizei n, GLuint* ids) {
	MGLUnimplementedOGLES(@"glGenQueriesEXT");
}

GLvoid glDeleteQueriesEXT(GLsizei n, const GLuint* ids) {
	MGLUnimplementedOGLES(@"glDeleteQueriesEXT");
}

GLboolean glIsQueryEXT(GLuint id) {
	MGLUnimplementedOGLES(@"glIsQueryEXT");
	return false;
}

GLvoid glBeginQueryEXT(GLenum target, GLuint id) {
	MGLUnimplementedOGLES(@"glBeginQueryEXT");
}

GLvoid glEndQueryEXT(GLenum target) {
	MGLUnimplementedOGLES(@"glEndQueryEXT");
}

GLvoid glGetQueryivEXT(GLenum target, GLenum pname, GLint* params) {
	MGLUnimplementedOGLES(@"glGetQueryivEXT");
}

GLvoid glGetQueryObjectuivEXT(GLuint id, GLenum pname, GLuint* params) {
	MGLUnimplementedOGLES(@"glGetQueryObjectuivEXT");
}

GLvoid glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program) {
	MGLUnimplementedOGLES(@"glUseProgramStagesEXT");
}

GLvoid glActiveShaderProgramEXT(GLuint pipeline, GLuint program) {
	MGLUnimplementedOGLES(@"glActiveShaderProgramEXT");
}

GLuint glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar* const* strings) {
	MGLUnimplementedOGLES(@"glCreateShaderProgramvEXT");
	return 0;
}

GLvoid glBindProgramPipelineEXT(GLuint pipeline) {
	MGLUnimplementedOGLES(@"glBindProgramPipelineEXT");
}

GLvoid glDeleteProgramPipelinesEXT(GLsizei n, const GLuint* pipelines) {
	MGLUnimplementedOGLES(@"glDeleteProgramPipelinesEXT");
}

GLvoid glGenProgramPipelinesEXT(GLsizei n, GLuint* pipelines) {
	MGLUnimplementedOGLES(@"glGenProgramPipelinesEXT");
}

GLboolean glIsProgramPipelineEXT(GLuint pipeline) {
	MGLUnimplementedOGLES(@"glIsProgramPipelineEXT");
	return false;
}

GLvoid glProgramParameteriEXT(GLuint program, GLenum pname, GLint value) {
	MGLUnimplementedOGLES(@"glProgramParameteriEXT");
}

GLvoid glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint* params) {
	MGLUnimplementedOGLES(@"glGetProgramPipelineivEXT");
}

GLvoid glValidateProgramPipelineEXT(GLuint pipeline) {
	MGLUnimplementedOGLES(@"glValidateProgramPipelineEXT");
}

GLvoid glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	MGLUnimplementedOGLES(@"glGetProgramPipelineInfoLogEXT");
}

GLvoid glProgramUniform1iEXT(GLuint program, GLint location, GLint x) {
	MGLUnimplementedOGLES(@"glProgramUniform1iEXT");
}

GLvoid glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y) {
	MGLUnimplementedOGLES(@"glProgramUniform2iEXT");
}

GLvoid glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z) {
	MGLUnimplementedOGLES(@"glProgramUniform3iEXT");
}

GLvoid glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w) {
	MGLUnimplementedOGLES(@"glProgramUniform4iEXT");
}

GLvoid glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x) {
	MGLUnimplementedOGLES(@"glProgramUniform1fEXT");
}

GLvoid glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y) {
	MGLUnimplementedOGLES(@"glProgramUniform2fEXT");
}

GLvoid glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z) {
	MGLUnimplementedOGLES(@"glProgramUniform3fEXT");
}

GLvoid glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	MGLUnimplementedOGLES(@"glProgramUniform4fEXT");
}

GLvoid glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) {
	MGLUnimplementedOGLES(@"glProgramUniform1ivEXT");
}

GLvoid glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) {
	MGLUnimplementedOGLES(@"glProgramUniform2ivEXT");
}

GLvoid glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) {
	MGLUnimplementedOGLES(@"glProgramUniform3ivEXT");
}

GLvoid glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint* value) {
	MGLUnimplementedOGLES(@"glProgramUniform4ivEXT");
}

GLvoid glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniform1fvEXT");
}

GLvoid glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniform2fvEXT");
}

GLvoid glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniform3fvEXT");
}

GLvoid glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniform4fvEXT");
}

GLvoid glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniformMatrix2fvEXT");
}

GLvoid glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniformMatrix3fvEXT");
}

GLvoid glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
	MGLUnimplementedOGLES(@"glProgramUniformMatrix4fvEXT");
}

GLvoid glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid** params) {
	MGLUnimplementedOGLES(@"glGetBufferPointervOES");
}

GLvoid* glMapBufferOES (GLenum target, GLenum access) {
	MGLUnimplementedOGLES(@"glMapBufferOES");
	return NULL;
}

GLboolean glUnmapBufferOES (GLenum target) {
	MGLUnimplementedOGLES(@"glUnmapBufferOES");
	return false;
}

GLvoid glBindVertexArrayOES(GLuint array) {
	MGLUnimplementedOGLES(@"glBindVertexArrayOES");
}

GLvoid glDeleteVertexArraysOES(GLsizei n, const GLuint* arrays) {
	MGLUnimplementedOGLES(@"glDeleteVertexArraysOES");
}

GLvoid glGenVertexArraysOES(GLsizei n, GLuint* arrays) {
	MGLUnimplementedOGLES(@"glGenVertexArraysOES");
}

GLboolean glIsVertexArrayOES(GLuint array) {
	MGLUnimplementedOGLES(@"glIsVertexArrayOES");
	return false;
}

#endif	// MLN_MACOS

