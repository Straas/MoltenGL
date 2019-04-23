/*
 * EAGL.m
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
 * This file provides an empty stub implementation of the OpenGL ES EAGL components for use with macOS.
 *
 * When using MoltenGL on macOS on a machine that does not support Metal, or if you have
 * chosen not to use Metal (by setting the build setting MGL_SUPPORT_OPENGL_ON_METAL=0),
 * your OpenGL ES app needs to be able to access a "native" OpenGL ES engine. macOS supports
 * OpenGL by default, and so an OpenGL ES implementation must be provided for use on macOS.
 *
 * To allow your app to compile, under macOS, add this source code file to your macOS app project.
 * Do not add this file to an iOS app, as iOS already provides a native OpenGL ES engine.
 *
 * This file represents the OpenGL ES EAGL behaviour required by MoltenGL when not using Metal,
 * but this default implementation does nothing. If your app requires OpenGL ES EAGL
 * functionality on macOS when not running Metal, you can add it here.
 */

#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <QuartzCore/CAEAGLLayer.h>

#if MLN_MACOS

#undef CAEAGLLayer		// Remove any redeclaration of EAGLContext in EAGL.h for this file
#undef EAGLSharegroup	// Remove any redeclaration of EAGLSharegroup in EAGL.h for this file
#undef EAGLContext		// Remove any redeclaration of EAGLContext in EAGL.h for this file


#pragma mark -
#pragma mark CAEAGLLayer

@implementation CAEAGLLayer

@synthesize drawableProperties=_drawableProperties;
@synthesize presentsWithTransaction=_presentsWithTransaction;


#pragma mark Instantiation

-(instancetype) init {
	if ( (self = [super init]) ) {
		[self initLocal];
	}
	return self;
}

-(instancetype) initWithLayer: (id) layer {
	if ( (self = [super initWithLayer: layer]) ) {
		[self initLocal];
	}
	return self;
}

-(void) initLocal {
	_drawableProperties = @{};			// retained
	_presentsWithTransaction = NO;
}

@end


#pragma mark -
#pragma mark EAGLSharegroup

@implementation EAGLSharegroup {
	NSString* _debugLabel;
}

@synthesize debugLabel=_debugLabel;

-(void) dealloc {
	[_debugLabel release];
	[super dealloc];
}


#pragma mark Instantiation

-(instancetype) init {
	if ( (self = [super init]) ) {
		_debugLabel = nil;
	}
	return self;
}

@end


#pragma mark -
#pragma mark EAGLContext and drawable extension

NSString* const kEAGLDrawablePropertyRetainedBacking	= @"EAGLDrawablePropertyRetained";
NSString* const kEAGLDrawablePropertyColorFormat		= @"EAGLDrawablePropertyColorFormat";
NSString* const kEAGLColorFormatRGBA8					= @"EAGLColorFormat8888";
NSString* const kEAGLColorFormatRGB565					= @"EAGLColorFormat565";
NSString* const kEAGLColorFormatSRGBA8					= @"EAGLColorFormatS8888";

@implementation EAGLContext {
	EAGLSharegroup* _sharegroup;
	NSString* _debugLabel;
	EAGLRenderingAPI _api;
}

@synthesize API=_api;
@synthesize sharegroup=_sharegroup;
@synthesize debugLabel=_debugLabel;

-(void) dealloc {
	[_sharegroup release];
	[_debugLabel release];

	[super dealloc];
}

-(BOOL) renderbufferStorage: (NSUInteger) target fromDrawable: (id<EAGLDrawable>) drawable {
	return YES;
}

-(BOOL) presentRenderbuffer: (NSUInteger) target {
	return YES;
}


#pragma mark Instantiation

-(instancetype) init { return [self initWithAPI: 0 sharegroup: nil]; }

-(instancetype) initWithAPI: (EAGLRenderingAPI) api { return [self initWithAPI: api sharegroup: nil]; }

-(instancetype) initWithAPI: (EAGLRenderingAPI) api sharegroup: (EAGLSharegroup*) sharegroup {
	if ( (self = [super init]) ) {
		_sharegroup = sharegroup ? [sharegroup retain] : [EAGLSharegroup new];	// retained
		_api = api;
		_debugLabel = nil;
	}
	return self;
}

static EAGLContext* _currentContext = nil;

+(EAGLContext*) currentContext { return _currentContext; }

+(BOOL) setCurrentContext:(EAGLContext*) context {
	if (context == _currentContext) { return YES; }
	[_currentContext release];
	[_currentContext retain];
	return YES;
}

@end

#endif	// MLN_MACOS

