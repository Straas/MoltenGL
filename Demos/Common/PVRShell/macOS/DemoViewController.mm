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


#pragma mark DemoViewController

@implementation DemoViewController

/** Since this is a single-view app, creates the OpenGL context and sets it in the GLK view. */
-(void) viewDidLoad {
	[super viewDidLoad];

	glActivateMoltenGLLicensesMGL();

	// If we won't be using Metal, disable it before creating the OpenGL context.
	// The glDisableMGL() command can  be used by the app to turn Metal off in Mac/OSX
	// configurations that don't support it. Must be done before Metal or OpenGL have been used.
#if !MGL_SUPPORT_OPENGL_ON_METAL
	glDisableMGL(GL_OPENGL_USE_METAL_MGL);
#endif

	GLKView *view = (GLKView*)self.view;

	// On OSX, OpenGL ES does not use EAGLContext, so it is only available
	// as part of MoltenGL if Metal is active.
	if (glIsEnabledMGL(GL_OPENGL_USE_METAL_MGL)) {
		EAGLContext* ctx = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES2];
		[EAGLContext setCurrentContext: ctx];
		view.context = ctx;
	}

	// Since OSX does not natively support GLKView, configuration properties
	// cannot be set in Interface Builder, so we set them here.
	view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

	CGSize viewSize = view.bounds.size;
	CGSize scaledViewSize = [view convertSizeToBacking: viewSize];

	NSLog(@"%@ framebuffer sized to width %i and height %i from view width %i and height %i", [view class],
		  (int)scaledViewSize.width, (int)scaledViewSize.height, (int)viewSize.width, (int)viewSize.height);

	[self initPVRShellWithSize: scaledViewSize];

	[self initDisplayLoop];
}

-(void) viewDidAppear {
	NSWindow* window = self.view.window;

	// Set up keyboard and mouse response
	[window makeFirstResponder: self];

	// Native OpenGL ES implementation does not support resizing the window
	if ( !glIsEnabledMGL(GL_OPENGL_USE_METAL_MGL) ) {
		window.styleMask &= ~NSResizableWindowMask;
	}
}

/** Initializes the PVRShell, which provides support for demo loading and rendering. */
-(void) initPVRShellWithSize: (CGSize) viewSize {

	// Uncomment to see the GLSL shader code converted to MGL before you eyes!
//	glEnable(GL_LOG_SHADER_CONVERSION_SOURCE_CODE_MGL);

	m_pPVRShellInit = new PVRShellInit;
	m_pPVRShellInit->Init();
	m_pPVRShellInit->m_pView = self.view;

	PVRShell* pPVRShell = m_pPVRShellInit->m_pShell;
	pPVRShell->PVRShellSet(prefWidth,  viewSize.width);
	pPVRShell->PVRShellSet(prefHeight, viewSize.height);

	// Optional command line input emulation
	char pszCL[] = "";
	m_pPVRShellInit->CommandLine(pszCL);

	// set up file paths
	NSString* readPath = [NSString stringWithFormat:@"%@%@", [[NSBundle mainBundle] bundlePath], @"/Contents/Resources/"];
	m_pPVRShellInit->SetReadPath([readPath UTF8String]);

	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	m_pPVRShellInit->SetWritePath([documentsDirectory UTF8String]);

	// If Metal is being used, initialize the PVR state.
	// If OpenGL is being used, this will happen the first time through the rendering loop.
	if (glIsEnabledMGL(GL_OPENGL_USE_METAL_MGL)) {
		pPVRShell->InitApplication();
		pPVRShell->InitView();
	}
}

/** Renders the demo scene. */
-(void) glkView: (GLKView*) view drawInRect: (CGRect) rect {
	m_pPVRShellInit->m_pShell->RenderScene();
}


#pragma mark Display loop

/** Rendering loop callback function for use with a CVDisplayLink. */
static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink,
									const CVTimeStamp* now,
									const CVTimeStamp* outputTime,
									CVOptionFlags flagsIn,
									CVOptionFlags* flagsOut,
									void* target) {

	DemoViewController* viewController = (DemoViewController*)target;

	// If we're using Metal, we can simply use the standard GLKView display method.
	// Otherwise, under OSX, since native GLKView functionality cannot be provided,
	// we make use of the PVRShell functionality to prepare and render using a native
	// OpenGL ES emulator on OSX.
	if (glIsEnabledMGL(GL_OPENGL_USE_METAL_MGL)) {
		DemoView* view = (DemoView*)viewController.view;
		[view display];
	} else {
		viewController->m_pPVRShellInit->Run();
	}

	return kCVReturnSuccess;
}

/** 
 * Creates a display link capable of being used with all active displays,
 * sets the callback function, and starts it up. 
 */
-(void) initDisplayLoop {
	[self endDisplayLoop];		// In case it's already going

	CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
	CVDisplayLinkSetOutputCallback(_displayLink, &DisplayLinkCallback, self);
	CVDisplayLinkStart(_displayLink);
}

/** Releases the display link. */
-(void) endDisplayLoop {
    CVDisplayLinkRelease(_displayLink);
}

-(void) dealloc {
	// In ordinary circumstances this isn't called
	m_pPVRShellInit->m_eState = ePVRShellReleaseView;
	delete(m_pPVRShellInit);

	[self endDisplayLoop];

	[super dealloc];
}


#pragma mark User event handling

-(BOOL) acceptsFirstResponder { return YES; }

/** Keyboard event handler. Simply map the events to PVRShell events. */
-(void) keyDown: (NSEvent*) event {
	if( !m_pPVRShellInit ) { return; }

	switch(event.keyCode) {
		case 0x12: m_pPVRShellInit->KeyPressed(PVRShellKeyNameACTION1); break;			// kVK_ANSI_1
		case 0x13: m_pPVRShellInit->KeyPressed(PVRShellKeyNameACTION2); break;			// kVK_ANSI_2

		case 0x31: m_pPVRShellInit->KeyPressed(PVRShellKeyNameSELECT); break;			// kVK_Space

		case 0x69: m_pPVRShellInit->KeyPressed(PVRShellKeyNameScreenshot); break;		// kVK_F13

		case 0x7B: m_pPVRShellInit->KeyPressed(m_pPVRShellInit->m_eKeyMapLEFT); break;	// kVK_LeftArrow
		case 0x7C: m_pPVRShellInit->KeyPressed(m_pPVRShellInit->m_eKeyMapRIGHT); break;	// kVK_RightArrow
		case 0x7D: m_pPVRShellInit->KeyPressed(m_pPVRShellInit->m_eKeyMapDOWN); break;	// kVK_DownArrow
		case 0x7E: m_pPVRShellInit->KeyPressed(m_pPVRShellInit->m_eKeyMapUP); break;	// kVK_UpArrow

		case 0x35: m_pPVRShellInit->KeyPressed(PVRShellKeyNameQUIT); break;				// kVK_Escape
	}
}

/** 
 * Populates the specified two-element array with the X & Y coordinates of the specified 
 * mouse event, within the local coordinate system of this controller's view.
 */
-(void) populateMouseLocation: (float*) mouseXY fromEvent: (NSEvent*) event {
	NSPoint location = [self.view convertPoint: event.locationInWindow fromView: nil];
	CGSize viewSize = self.view.frame.size;
	mouseXY[0] = location.x / viewSize.width;
	mouseXY[1] = 1.0f - (location.y / viewSize.height);
}

/** Mouse event handler. Simply map the events to PVRShell events. */
-(void) mouseDown: (NSEvent*) event {
	if( !m_pPVRShellInit ) { return; }

	float mouseXY[2];
	[self populateMouseLocation: mouseXY fromEvent: event];
	m_pPVRShellInit->TouchBegan(mouseXY);
}

/** Mouse event handler. Simply map the events to PVRShell events. */
-(void) mouseUp: (NSEvent*) event {
	if( !m_pPVRShellInit ) { return; }

	float mouseXY[2];
	[self populateMouseLocation: mouseXY fromEvent: event];
	m_pPVRShellInit->TouchEnded(mouseXY);
}

/** Mouse event handler. Simply map the events to PVRShell events. */
-(void) mouseDragged: (NSEvent*) event {
	if( !m_pPVRShellInit ) { return; }

	float mouseXY[2];
	[self populateMouseLocation: mouseXY fromEvent: event];
	m_pPVRShellInit->TouchMoved(mouseXY);
}

@end

#pragma mark DemoView

@implementation DemoView
@end


#pragma mark OSX specific PVRShell functionality

// Empty stub. OS init handled in DemoViewController initPVRShellWithSize:
void ObjC_OSInit(PVRShellInit* pInit) {}

// Empty stub. View and window config handled by Storyboard.
bool ObjC_OSInitOS(PVRShellInit* pOS) { return true; }

// Empty stub. Unused.
bool ObjC_OSGet(PVRShellInit* pInit, const prefNameIntEnum prefName, int *pn) { return false; }

// Empty stub. Unused.
bool ObjC_ExitMessage(PVRShellInit* pInit, const char * const pExitMessage) { return true; }

