/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "grid.h"
#include "CaptureCubeUpdater.h"
#include "ImageCubeUpdater.h"
#include "Configuration.h"
#include "OpenCVTexture.h"

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyReleased( const OIS::KeyEvent& evt );


    void adjust_scale(int amount);
    void adjust_step(int amount);

private:
    //bool processUnbufferedInput(const Ogre::FrameEvent& evt);

    OpenCVTexture*  _opencv_texture;
    Configuration*  _config;
    CubeUpdater*    _cubeUpdater;
    Grid*           _grid;
    int             _scaleSkipCounter;
    bool            _needsRedraw;



};

#endif // #ifndef __TutorialApplication_h_
