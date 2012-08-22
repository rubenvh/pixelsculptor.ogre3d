#ifndef OPENCVTEXTURE_H
#define OPENCVTEXTURE_H

#include <iostream>
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "BaseApplication.h"

class OpenCVTexture
{
    public:
        OpenCVTexture(std::string texture_name, int width, int height);
        virtual ~OpenCVTexture();

        void update(cv::Mat* image);

        std::string get_texture_name() { return _name; }
        std::string get_material_name() { return _name+"_material"; }
        Ogre::TexturePtr get_texture() { return _texture; }
        Ogre::MaterialPtr get_material() { return _material; }
        Ogre::HardwarePixelBufferSharedPtr get_pixelbuffer() { return _pixelBuffer; }
    protected:
    private:
        std::string                         _name;
        Ogre::HardwarePixelBufferSharedPtr  _pixelBuffer;
        Ogre::TexturePtr                    _texture;
        Ogre::MaterialPtr                   _material;
};

#endif // OPENCVTEXTURE_H
