#include "../include/CubeUpdater.h"

using namespace std;
using namespace Ogre;

CubeUpdater::CubeUpdater(Configuration* config): _config(config)
{
    //ctor
    is_first_update = true;
}

float CubeUpdater::get_color(uint8_t p)
{
    return (float) p / 255.0f;
}

float CubeUpdater::scale_value(float oldvalue, float newvalue, float scaling, float minimal_delta)
{
    if (oldvalue < newvalue+minimal_delta &&
        oldvalue > newvalue-minimal_delta) return newvalue;

    float delta = (newvalue-oldvalue)*scaling;
    return oldvalue + delta;
}

void CubeUpdater::apply_color(Ogre::Entity* entity, float r, float g, float b)
{
    Ogre::MaterialPtr manObj = entity->getSubEntity(0)->getMaterial();
    float newR(r/255.0f), newG(g/255.0f), newB(b/255.0f);
    ColourValue oldColor(manObj->getTechnique(0)->getPass(0)->getDiffuse());

    if (oldColor.r == newR && oldColor.g == newG && oldColor.b == newB)
    {
        return;
    }

    if (!is_first_update)
    {
        cout << "New color " << newR << ", " << newG << ", " << newB << " | ";
        cout << "Old color " << oldColor.r << ", " << oldColor.g << ", " << oldColor.b << " | ";
        cout << "Diff = " << newR-oldColor.r<< endl;

        newR = scale_value(oldColor.r, newR, _config->get<double>("application.grid.adaptive_factor"), 0.01);
        newG = scale_value(oldColor.g, newG, _config->get<double>("application.grid.adaptive_factor"), 0.01);
        newB = scale_value(oldColor.b, newB, _config->get<double>("application.grid.adaptive_factor"), 0.01);

        cout << "Actual New color " << newR << ", " << newG << ", " << newB << endl;

    }

//
    manObj->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(newR, newG, newB));
    manObj->getTechnique(0)->getPass(0)->setAmbient(Ogre::ColourValue(newR/2.0f, newG/2.0f, newB/2.0f));
    //manObj->getTechnique(0)->getPass(0)->setSelfIllumination(Ogre::ColourValue(r, g, b));
}

void CubeUpdater::apply_scale(Ogre::SceneNode* node, float w, float d, float h)
{
    int scale(_config->get<int>("application.grid.scale"));
    Ogre::Vector3 oldScale = node->getScale()*255.0f/((float)scale/2.0f);
    Ogre::Vector3 newScale(w, h, d);

    if (oldScale.x == w && oldScale.y == h && oldScale.z == d)
    {
        // TODO: never get here due to conversion problems
        cout << "Same scale, no work needed"<<endl;
        return;
    }

    if (!is_first_update)
    {
//        cout << "New scale " << w << ", " << h << ", " << d << " | ";
//        cout << "Old scale " << oldScale.x << ", " << oldScale.y << ", " << oldScale.z << " | ";
//        cout << "Diff = " << w-oldScale.x<< endl;

        newScale.x = scale_value(oldScale.x, w, _config->get<double>("application.grid.adaptive_factor"), 0.01);
        newScale.y = scale_value(oldScale.y, h, _config->get<double>("application.grid.adaptive_factor"), 0.01);
        newScale.z = scale_value(oldScale.z, d, _config->get<double>("application.grid.adaptive_factor"), 0.01);

//        cout << "Actual new scale " << newScale.x << ", " << newScale.y << ", " << newScale.z << endl;
    }

    node->setScale((newScale*((float)scale/2.0f))/255.0f);
}

void CubeUpdater::do_update_base(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y)
{
    cv::Mat* image = get_resized_image();

    cv::Vec3b rgb = image->at<cv::Vec3b>(y, x);

//    cout << (float) rgb.val[1] << " "  << (float) rgb.val[0] << " " << (float)rgb.val[2]<<endl;
    apply_scale(node, (float) rgb.val[1], (float) rgb.val[0], (float)rgb.val[2]);

    apply_color(entity, (float) rgb.val[2], (float) rgb.val[1], (float) rgb.val[0]);

    // set position of objects
    int step = _config->get<int>("application.grid.step");
    int xpos = (int)(x*step - _config->get<int>("application.grid.cols")*step*1.0/2.0);
    int ypos = (int)(y*step - _config->get<int>("application.grid.rows")*step*1.0/2.0);
    node->setPosition(Ogre::Vector3(xpos, node->getScale().y, ypos));

    is_first_update = false;
}
