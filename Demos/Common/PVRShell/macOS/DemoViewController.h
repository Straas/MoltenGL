/*
 * DemoViewController.h
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

#import "PVRShell.h"
#import <AppKit/AppKit.h>
#import <GLKit/GLKView.h>


#pragma mark DemoViewController

/** The main GLKit view controller for the demo storyboard. */
@interface DemoViewController : NSViewController <GLKViewDelegate> {
	PVRShell*			m_pPVRShell;
	PVRShellInit*		m_pPVRShellInit;
	CVDisplayLinkRef	_displayLink;
}

@end


#pragma mark DemoView

/**
 * The main GLKit view for the demo Storyboard.
 *
 * This is an empty GLKView subclass so that MoltenGL can redirect the GLKView parent
 * class to a Metal-based substitute during the loading of the Storyboard.
 */
@interface DemoView : GLKView
@end

