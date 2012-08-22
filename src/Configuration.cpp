#include "../include/Configuration.h"

using namespace libconfig;
using namespace std;


Configuration::Configuration(const string& file): _filename(file)
{
    try
    {
        /* Load the configuration.. */
        cout << "loading [" << file << "]...";
        _config.readFile(file.c_str());
        cout << "ok" << endl;


        /*_history = this->get<int>("application.bgsubtractor.history");
        _nmixtures = this->get<int>("application.bgsubtractor.nmixtures");
        _backgroundratio = this->get<int>("application.bgsubtractor.bg_ratio");
        _noisesigma = this->get<int>("application.bgsubtractor.noise_sigma");
        _dilation_iters = this->get<int>("application.bgsubtractor.dilation_iterations");
        _erosion_iters = this->get<int>("application.bgsubtractor.erosion_iterations");
        _update_bgmodel = this->get<bool>("application.bgsubtractor.update_bgmodel");
        */
  }
  catch (...)
  {
    cout << "failed" << endl;
  }


}

Configuration::~Configuration()
{
    /*this->set<int>("application.bgsubtractor.history", _history);
    this->set<int>("application.bgsubtractor.nmixtures", _nmixtures);
    this->set<int>("application.bgsubtractor.bg_ratio", _backgroundratio);
    this->set<int>("application.bgsubtractor.noise_sigma", _noisesigma);
    this->set<int>("application.bgsubtractor.dilation_iterations", _dilation_iters);
    this->set<int>("application.bgsubtractor.erosion_iterations", _erosion_iters);
    this->set<bool>("application.bgsubtractor.update_bgmodel", _update_bgmodel);*/
    // Save the configuration
    cout << "saving [" << _filename << "]..";
    _config.writeFile(_filename.c_str());
    cout << "ok" << endl;
}
