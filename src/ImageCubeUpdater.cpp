#include "../include/ImageCubeUpdater.h"

using namespace std;
using namespace cv;

ImageCubeUpdater::ImageCubeUpdater(Configuration* config):
    CubeUpdater(config)
{
    _has_more = true;

    string filename = _config->get<string>("application.capture.imagesource");
    cout << "ImageCubeUpdater::loading image " << filename << endl;
    // load the image

    Mat temp = imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);

    if (!temp.data)
    {
        cerr << "Could not open or find the image '"<<filename<<"'"<<endl;
    }

    resize(temp, _image,
           cvSize(
                  _config->get<int>("application.capture.size.width"),
                  _config->get<int>("application.capture.size.height")));
    resize(_image, _resized_image, cvSize(_config->get<int>("application.grid.cols"),_config->get<int>("application.grid.rows")));

}

ImageCubeUpdater::~ImageCubeUpdater()
{
}

bool ImageCubeUpdater::has_more()
{
    return _has_more;
}

void ImageCubeUpdater::prepare()
{

    // TODO: make has_more() return false
    //_has_more = false;
}


void ImageCubeUpdater::do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y)
{
    if (_image.data)
    {
        CubeUpdater::do_update_base(node, entity, x, y);
    }
}
