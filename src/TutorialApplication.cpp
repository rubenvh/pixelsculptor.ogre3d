/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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
#include "../include/TutorialApplication.h"

using namespace std;

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
    _scaleSkipCounter = 0;
    _config = new Configuration("config.cfg");

    if (_config->get<string>("application.capture.updater")=="image")
    {
        _cubeUpdater = new ImageCubeUpdater(_config);
    }
    else
    {
        _cubeUpdater = new CaptureCubeUpdater(_config);
    }

    _grid = new Grid(
                     _config->get<int>("application.grid.rows"),
                     _config->get<int>("application.grid.cols"),
                     _config->get<int>("application.grid.step"),
                     _config->get<int>("application.grid.width"),
                     _config->get<int>("application.grid.height"));
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
    delete _grid;
    delete _cubeUpdater;
    delete _config;
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    srand ( time(NULL) );

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

     //Create a light
    Ogre::Light* myLight = mSceneMgr->createLight("MainLight");
    myLight->setType(Ogre::Light::LT_POINT);
    myLight->setPosition(20, 40, 10);
    myLight->setDiffuseColour(1, 1, 1);
    myLight->setSpecularColour(1, 1, 1);

    //fog
    if (_config->get<bool>("application.ogre3d.fog"))
    {
        Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
        mWindow->getViewport(0)->setBackgroundColour(fadeColour);
        mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 200, 500);
        mSceneMgr->setFog(Ogre::FOG_EXP, fadeColour, 0.005);
    }

    // init grid
    _grid->init(_config->get<string>("application.ogre3d.model"),
                _config->get<string>("application.ogre3d.material"),
                mSceneMgr, &Ogre::MaterialManager::getSingleton());
    _grid->construct();


    // dynamic texture
    int texture_width = _config->get<int>("application.capture.size.width");
    int texture_height = _config->get<int>("application.capture.size.height");
//    int texture_width = _config->get<int>("application.grid.cols");
//    int texture_height = _config->get<int>("application.grid.rows");
    _opencv_texture = new OpenCVTexture("opencv_texture",texture_width, texture_height);

    // Create an overlay
    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
    Ogre::Overlay* overlay = overlayManager.create( "OverlayName" );

    // Create a panel
    Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "PanelName" ) );
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(10, 10);
    panel->setDimensions(texture_width, texture_height);
    panel->setMaterialName( _opencv_texture->get_material_name() );
    // Add the panel to the overlay
    overlay->add2D( panel );
    // Show the overlay
    overlay->show();

    // plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,    plane, _config->get<int>("application.grid.width"), _config->get<int>("application.grid.height"), 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
    entGround->setMaterialName("Scene/Ground");
    entGround->setCastShadows(false);
}

//-------------------------------------------------------------------------------------
/*bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    return true;
}
//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

    if(!processUnbufferedInput(evt)) return false;

    return ret;
}
*/
//-------------------------------------------------------------------------------------
bool TutorialApplication::frameStarted(const Ogre::FrameEvent& evt)
{
    _cubeUpdater->prepare();

    if (_cubeUpdater->has_more() || _needsRedraw)
    {
        if (++_scaleSkipCounter > _config->get<int>("application.ogre3d.frameskip"))
        {
            _scaleSkipCounter = 0;
            _grid->update(_cubeUpdater);
            _opencv_texture->update(_cubeUpdater->get_image());
//            _opencv_texture->update(_cubeUpdater->get_resized_image());

            if (_needsRedraw) _needsRedraw = false;
        }
    }



    return true;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::keyReleased( const OIS::KeyEvent& evt )
{
    //cout << "Key pressed: " << evt.key << endl;
    switch (evt.key)
    {
    case OIS::KC_A:
        adjust_scale(-1);
        break;
    case OIS::KC_Z:
        adjust_scale(1);
        break;
    case OIS::KC_Q:
        adjust_step(-1);
        break;
    case OIS::KC_S:
        adjust_step(1);
        break;
    default:
        return BaseApplication::keyReleased(evt);
    }
    return true;
}

void TutorialApplication::adjust_scale(int amount)
{
    int newScale = _config->get<int>("application.grid.scale")+amount;
    _config->set<int>("application.grid.scale", newScale);
    _needsRedraw = true;
}
void TutorialApplication::adjust_step(int amount)
{
    int newStep = _config->get<int>("application.grid.step")+amount;
    _config->set<int>("application.grid.step", newStep);
    _needsRedraw = true;
}





