/******************************************************************************

 @file         MGLPVRShell.cpp
 @copyright    Copyright (c) The Brenwill Workshop Limited.
 @brief        Makes programming for 3D APIs easier by wrapping surface
               initialization, Texture allocation and other functions for use by a demo.

******************************************************************************/

#include "MGLPVRShell.h"
#include <MoltenGL/mglext.h>
#include <OpenGLES/ES2/gl.h>

// No Doxygen for CPP files, due to documentation duplication
/// @cond NO_DOXYGEN


/*!***********************************************************************
 @brief		Constructor
*************************************************************************/
MGLPVRShell::MGLPVRShell() {
	m_fps = 0;
	m_lastFrameCountWindowTime = 0;
	m_frameCount = 0;
	m_frameCountWindow = 30;
}

/*!***********************************************************************
 @brief		Destructor
*************************************************************************/
MGLPVRShell::~MGLPVRShell() {}

void MGLPVRShell::MGLPVRShellUpdateFPS() {
	if (++m_frameCount < m_frameCountWindow) { return; }

	m_frameCount = 0;
	unsigned long currTime = PVRShellGetTime();
	m_fps = (m_frameCountWindow * 1000.0) / ((double)(currTime - m_lastFrameCountWindowTime));
	m_lastFrameCountWindowTime = currTime;
}

int MGLPVRShell::MGLPVRShellGetFPS() { return m_fps; }

unsigned long MGLPVRShell::MGLPVRShellGetFrameCountWindow() { return m_frameCountWindow; }

void MGLPVRShell::MGLPVRShellSetFrameCountWindow(unsigned long value) { m_frameCountWindow = value; }

EPVRTError MGLPVRShell::DisplayTitle(const char * const pszTitle) {
#ifdef DEBUG
	bool isDebug = true;
#else
	bool isDebug = false;
#endif

	int strSize = 256;
	char title[strSize];
	char desc[strSize];
	bool isUsingMetal = (MGL_SUPPORT_OPENGL_ON_METAL) && glIsEnabled(GL_OPENGL_USE_METAL_MGL);

	snprintf(title, strSize, "%s%s", pszTitle, (isDebug ? " [DEBUG]" : ""));
	snprintf(desc, strSize, "Rendering using %s", (isUsingMetal ? "MoltenGL" : "OpenGL ES"));
	return m_Print3D.DisplayDefaultTitle(title, desc, ePVRTPrint3DSDKLogo);
}

/// @endcond
//NO_DOXYGEN

