#ifndef IMAGECUBEUPDATER_H
#define IMAGECUBEUPDATER_H

#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CubeUpdater.h"
#include "Configuration.h"

class ImageCubeUpdater : public CubeUpdater
{
    public:
        ImageCubeUpdater(Configuration* config);
        virtual ~ImageCubeUpdater();

        virtual bool has_more();
        virtual void prepare();
        virtual void do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y);
        virtual cv::Mat* get_image() { return &_image; }
        virtual cv::Mat* get_resized_image() { return &_resized_image; }
    protected:
    private:
        bool            _has_more;
        cv::Mat          _image;
        cv::Mat          _resized_image;

};

#endif // IMAGECUBEUPDATER_H
