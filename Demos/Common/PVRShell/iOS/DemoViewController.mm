/*
 * DemoViewController.mm
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

#import "DemoViewController.h"

#include "PVRShellAPI.h"
#include "PVRShellOS.h"
#include "PVRShellImpl.h"
#import <MoltenGL/mglext.h>

@implementation DemoViewController

/** Since this is a single-view app, creates the OpenGL context and sets it in the GLK view. */
-(void) viewDidLoad {
	[super viewDidLoad];

	glActivateMoltenGLLicensesMGL();

	EAGLContext* ctx = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES2];
	[EAGLContext setCurrentContext: ctx];

	GLKView *view = (GLKView*)self.view;
	view.context = ctx;

	CGSize viewSize = view.bounds.size;
	CGFloat scale = view.contentScaleFactor;
	CGSize scaledViewSize = CGSizeMake(viewSize.width * scale, viewSize.height * scale);

	NSLog(@"GLKView framebuffer sized to width %i and height %i from view width %i and height %i and content scale %.3f",
		  (int)scaledViewSize.width, (int)scaledViewSize.height, (int)viewSize.width, (int)viewSize.height, self.view.contentScaleFactor);

	[self initPVRShellWithSize: scaledViewSize];
}

/** Initializes the PVRShell, which provides support for demo loading and rendering. */
-(void) initPVRShellWithSize: (CGSize) viewSize {

	// Uncomment to see the GLSL shader code converted to MGL before you eyes!
//	glEnable(GL_LOG_SHADER_CONVERSION_SOURCE_CODE_MGL);

	m_pPVRShellInit = new PVRShellInit;
	m_pPVRShellInit->Init();

	PVRShell* pPVRShell = m_pPVRShellInit->m_pShell;
	pPVRShell->PVRShellSet(prefWidth,  viewSize.width);
	pPVRShell->PVRShellSet(prefHeight, viewSize.height);

	// Optional command line input emulation
	char pszCL[] = "";
	m_pPVRShellInit->CommandLine(pszCL);

	// set up file paths
	NSString* readPath = [NSString stringWithFormat:@"%@%@", [[NSBundle mainBundle] bundlePath], @"/"];
	m_pPVRShellInit->SetReadPath([readPath UTF8String]);

	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	m_pPVRShellInit->SetWritePath([documentsDirectory UTF8String]);

	pPVRShell->InitApplication();
	pPVRShell->InitView();
}

/** Renders the demo scene. */
-(void) glkView: (GLKView*) view drawInRect: (CGRect) rect {
	m_pPVRShellInit->m_pShell->RenderScene();
}

/** Handles the start of a touch action. */
-(void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event {
	if (touches.count != 1) { return; }

	UIView* view = self.view;
	CGFloat viewScale = view.contentScaleFactor;

	for(UITouch* touch in touches) {
		CGPoint touchLocation = [touch locationInView: view];
		touchLocation.x *= viewScale;
		touchLocation.y *= viewScale;
		float Position[2] = { touchLocation.x, touchLocation.y };
		m_pPVRShellInit->BeganTouch(Position, m_pPVRShellInit);
	}
}

/** Handles the continuation of a touch action. */
-(void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event {
	if (touches.count != 1) { return; }

	UIView* view = self.view;
	CGFloat viewScale = view.contentScaleFactor;

	for(UITouch* touch in touches) {
		CGPoint touchLocation = [touch locationInView: view];
		touchLocation.x *= viewScale;
		touchLocation.y *= viewScale;
		float position[2] = { touchLocation.x, touchLocation.y };
		m_pPVRShellInit->MovedTouch(position, m_pPVRShellInit);
	}
}

/** Handles the end of a touch action. */
-(void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event {
	if (touches.count != 1) { return; }

	UIView* view = self.view;
	CGFloat viewScale = view.contentScaleFactor;

	for(UITouch* touch in touches) {
		CGPoint touchLocation = [touch locationInView: view];
		touchLocation.x *= viewScale;
		touchLocation.y *= viewScale;
		float position[2] = { touchLocation.x, touchLocation.y };
		m_pPVRShellInit->EndedTouch(position, m_pPVRShellInit);
	}
}

-(void) dealloc {
	// In ordinary circumstances this isn't called
	m_pPVRShellInit->m_eState = ePVRShellReleaseView;
	delete(m_pPVRShellInit);

	[super dealloc];
}

@end

@implementation DemoView
@end

