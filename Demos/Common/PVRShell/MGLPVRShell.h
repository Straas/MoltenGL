/*!****************************************************************************

 @file       MGLPVRShell.h
 @copyright  Copyright (c) The Brenwill Workshop Ltd.
 @brief      Makes programming for 3D APIs easier by wrapping surface
             initialization, Texture allocation and other functions for use by a demo.

******************************************************************************/

#ifndef __MGLPVRSHELL_H_
#define __MGLPVRSHELL_H_

/*****************************************************************************/
/*! @mainpage MGLPVRShell
******************************************************************************/

/*****************************************************************************
** Includes
*****************************************************************************/
#include "PVRShell.h"
#include "PVRTPrint3D.h"

/*!***************************************************************************
 @class    MGLPVRShell
 @brief    Inherited by the application; responsible for abstracting the OS and API.
 @details  PVRShell is the main Shell class that an application uses. An
           application should supply a class which inherits PVRShell and supplies
           implementations of the virtual functions of PVRShell (InitApplication(),
           QuitApplication(), InitView(), ReleaseView(), RenderScene()). Default stub
           functions are supplied; this means that an application is not
           required to supply a particular function if it does not need to do anything
           in it.
           The other, non-virtual, functions of PVRShell are utility functions that the
           application may call.
 *****************************************************************************/
class MGLPVRShell : public PVRShell {

public:
	// Print3D class used to display text
	CPVRTPrint3D m_Print3D;

	int m_fps = 0;
	unsigned long m_lastFrameCountWindowTime = 0;
	unsigned long m_frameCount = 0;
	unsigned long m_frameCountWindow = 30;

public:
    /*!***********************************************************************
    @brief      Constructor
    *************************************************************************/
	MGLPVRShell();

    /*!***********************************************************************
    @brief      Destructor
    *************************************************************************/
    virtual ~MGLPVRShell();

    /* MGLPVRShell functions available for the application to use. */

    /*!***********************************************************************
     @brief     This function should be called at the beginning of each frame render
				to measure the current frames per second (FPS) metric, which is availble
				in the m_fps instance variable.
                Although this function must be called on each frame, the value of the 
				m_fps is only updated every m_frameCountWindow frames (once or twice per
				second), to help average out the value, as it is meant to be read by humans.
    *************************************************************************/
    void MGLPVRShellUpdateFPS();

	/*!***********************************************************************
	 @brief      Returns the current average frames per second.
	 @return     The current average frames per second.
	 *************************************************************************/
	int MGLPVRShellGetFPS();

	/*!***********************************************************************
	 @brief     Indicates how often the value returned by MGLPVRShellGetFPS() and the 
				m_fps instance value are updated. Returns the number of times the 
				MGLPVRShellUpdateFPS() function must be called before the value returned
				by the MGLPVRShellGetFPS() is modiied.
	 @return    The number of frames that must pass before the frames per second value is updated.
	 *************************************************************************/
	unsigned long MGLPVRShellGetFrameCountWindow();

	/*!***********************************************************************
	 @brief     Sets how often the value returned by MGLPVRShellGetFPS() and the
				m_fps instance value are updated.
	 @param[in] value	The number of times the MGLPVRShellUpdateFPS() function must be 
						called before the value returned by the MGLPVRShellGetFPS() is modiied.
	 *************************************************************************/
	void MGLPVRShellSetFrameCountWindow(unsigned long value);

	/*!***********************************************************************
	 @brief     Displays the specified title at the top left of the screen, and a description 
				of whether Metal or OpenGL is performing the current rendering.
	 @param[in] pszTitle	The text to display as the title.
	 @return     An error result.
	 *************************************************************************/
	EPVRTError DisplayTitle(const char * const pszTitle);

};

#endif /* __PVRSHELL_H_ */

/*****************************************************************************
 End of file (PVRShell.h)
*****************************************************************************/

