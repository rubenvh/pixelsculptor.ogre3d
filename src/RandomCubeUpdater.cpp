#include "../include/RandomCubeUpdater.h"

RandomCubeUpdater::RandomCubeUpdater()
{
    //ctor
}

RandomCubeUpdater::~RandomCubeUpdater()
{
    //dtor
}

void RandomCubeUpdater::prepare()
{


}
void RandomCubeUpdater::do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y)
{
    // scale objects randomly
    int heightScale = rand()%5+1;
    node->setScale(Ogre::Vector3(rand()%5+1, heightScale, rand()%5+1));

    // place objects on ground
    node->setPosition(Ogre::Vector3(node->getPosition().x, heightScale, node->getPosition().z));
}
