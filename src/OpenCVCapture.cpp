#include "../include/OpenCVCapture.h"

using namespace cv;
using namespace std;

OpenCVCapture::OpenCVCapture(Configuration* config): _config(config)
{
    _capture = new VideoCapture();
}

OpenCVCapture::~OpenCVCapture()
{
    _capture->release();
    delete _capture;
}

void OpenCVCapture::init()
{
    if (_config->get<bool>("application.capture.is_camera"))
    {
        _capture->open(_config->get<int>("application.capture.camera"));
    }
    else
    {
        std::string temp = _config->get<std::string>("application.capture.capturesource");
        cout << "Using '" << temp << "' as input file." << endl;
        _capture->open(temp);
    }


    if( !_capture->isOpened() )
    {
        printf("\nCan not open camera or video file\n");
        exit(-1);
    }

    _capture->set(CV_CAP_PROP_FRAME_WIDTH, _config->get<int>("application.capture.size.width"));
    _capture->set(CV_CAP_PROP_FRAME_HEIGHT, _config->get<int>("application.capture.size.height"));

    *_capture >> _raw_input_frame;
    if(!_raw_input_frame.data)
    {
        printf("can not read data from the video source\n");
        exit(-1);
    }
}

cv::Mat* OpenCVCapture::get_frame()
{
    *_capture >> _raw_input_frame;

    return &_raw_input_frame;
}

bool OpenCVCapture::has_frame()
{
    return _raw_input_frame.data;
}

