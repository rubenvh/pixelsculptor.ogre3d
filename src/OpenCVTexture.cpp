#include "../include/OpenCVTexture.h"

using namespace cv;
using namespace std;

OpenCVTexture::OpenCVTexture(std::string texture_name, int width, int height):
    _name(texture_name)
{
    //ctor
    _texture =
        Ogre::TextureManager::getSingleton().createManual(get_texture_name(),
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Ogre::TEX_TYPE_2D, width, height, 0, Ogre::PF_R8G8B8A8,
        Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
    _pixelBuffer = _texture->getBuffer();

    // Create a material using the texture
   _material = Ogre::MaterialManager::getSingleton().create( get_material_name(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
   _material->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( get_texture_name() );
   _material->getTechnique( 0 )->getPass( 0 )->setSceneBlending( Ogre::SBT_TRANSPARENT_ALPHA );
}

OpenCVTexture::~OpenCVTexture()
{
    //dtor
}

void OpenCVTexture::update(cv::Mat* image)
{
    if (image != 0)
    {
        int w(image->cols);
        int h(image->rows);

        //cout << "Copying IplImage to texture (width:"<<w<<",height:"<<h<<")"<<endl;

        _pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
        const Ogre::PixelBox& pixelBox = _pixelBuffer->getCurrentLock();
        Ogre::uint8* pDest = static_cast<Ogre::uint8*> ( pixelBox.data );
        //Ogre::uint32 *pDest = static_cast<Ogre::uint32*>(pixelBox.data);

        //memcpy(pDest, image->data, image->cols * image->rows);
        for(int i=0; i<h; i++)
        {
            //uint32 *data = static_cast<uint32*>(pb.data) + i*pb.rowPitch;
            for(int j=0; j<w; j++)
            {
                cv::Vec3b rgb = image->at<cv::Vec3b>(i, j);

                pDest[((j+(i*w))*4)+2] = rgb.val[2]; //image->data[(j+(i*w)*3)];
                pDest[((j+(i*w))*4)+1] = rgb.val[1];//image->data[(j+(i*w)*3)+1];
                pDest[((j+(i*w))*4)] = rgb.val[0]; //image->data[(j+(i*w)*3)+2];


                pDest[((j+(i*w))*4)+3] = 255;
                //memcpy(pDest+((j+(i*w))*4), image->data+((j+(i*w))*4), 4);
            }
        }
        _pixelBuffer->unlock();
    }

}
