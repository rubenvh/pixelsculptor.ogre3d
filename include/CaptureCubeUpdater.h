#ifndef CAPTURECUBEUPDATER_H
#define CAPTURECUBEUPDATER_H


#include "CubeUpdater.h"
#include "OpenCVCapture.h"
#include "Configuration.h"
#include "opencv/cv.h"

class CaptureCubeUpdater : public CubeUpdater
{
    public:
        CaptureCubeUpdater(Configuration* config);
        virtual ~CaptureCubeUpdater();

        virtual bool has_more();
        virtual void prepare();
        virtual void do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y);
        virtual cv::Mat* get_image() { return &_input_frame; }
        virtual cv::Mat* get_resized_image() { return &_resized_frame; }
    protected:
    private:
        OpenCVCapture*  _capture;
        cv::Mat        _input_frame;
        cv::Mat        _resized_frame;
        uint8_t* _pixelPtr;
};

#endif // CAPTURECUBEUPDATER_H
