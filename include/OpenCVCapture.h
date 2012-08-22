#ifndef OPENCVCAPTURE_H
#define OPENCVCAPTURE_H

#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Configuration.h"

class OpenCVCapture
{
    public:
        OpenCVCapture(Configuration* config);
        virtual ~OpenCVCapture();

        void init();
        cv::Mat* get_frame();
        bool has_frame();
    protected:
    private:

        Configuration*      _config;
        cv::Mat             _raw_input_frame;
        cv::VideoCapture*   _capture;
};

#endif // OPENCVCAPTURE_H
