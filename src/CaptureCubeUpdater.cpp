#include "../include/CaptureCubeUpdater.h"
using namespace std;
using namespace cv;

CaptureCubeUpdater::CaptureCubeUpdater(Configuration* config):
    CubeUpdater(config)
{
    _capture = new OpenCVCapture(_config);
    _capture->init();
    //namedWindow("test", 1);
    //_input_frame = cvCreateIm
}

CaptureCubeUpdater::~CaptureCubeUpdater()
{
   delete _capture;
}

bool CaptureCubeUpdater::has_more()
{
    return _capture->has_frame();
}

void CaptureCubeUpdater::prepare()
{
    Mat* temp =  _capture->get_frame();

    int w = _config->get<int>("application.capture.size.width");
    int h = _config->get<int>("application.capture.size.height");
    if (temp->cols != w || temp->rows != h)
    {
        //cout << "Resizing captured image to " << w << " x " << h << endl;
         resize(*temp, _input_frame, cvSize(w, h));
    }
    else
    {
        _input_frame = *temp;
    }


    resize(_input_frame, _resized_frame,
               cvSize(
                      _config->get<int>("application.grid.cols"),
                      _config->get<int>("application.grid.rows")));


    //imshow("test", *_input_frame);
}

void CaptureCubeUpdater::do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y)
{
    CubeUpdater::do_update_base(node, entity, x, y);
}


