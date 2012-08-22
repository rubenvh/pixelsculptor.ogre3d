#ifndef CUBEUPDATER_H
#define CUBEUPDATER_H

#include <stdio.h>
#include <stdlib.h>
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "BaseApplication.h"
#include "Configuration.h"

class CubeUpdater
{
    public:
        CubeUpdater(Configuration* config);

        virtual bool has_more() = 0;
        virtual void prepare() = 0;
        virtual void do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y) = 0;
        virtual cv::Mat* get_image() = 0;
        virtual cv::Mat* get_resized_image() = 0;
        Ogre::HardwarePixelBufferSharedPtr PixelBuffer;
    protected:

        Configuration*  _config;

        //double scale_pixel(uint8_t p);
        float  get_color(uint8_t p);
        void    do_update_base(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y);
    private:
        float  scale_value(float oldvalue, float newvalue, float scaling, float minimal_delta);
        void    apply_scale(Ogre::SceneNode* node, float w, float d, float h);
        void    apply_color(Ogre::Entity* entity, float r, float g, float b);
        bool    is_first_update;
};

#endif // CUBEUPDATER_H
