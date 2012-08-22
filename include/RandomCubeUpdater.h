#ifndef RANDOMCUBEUPDATER_H
#define RANDOMCUBEUPDATER_H

#include "CubeUpdater.h"


class RandomCubeUpdater : public CubeUpdater
{
    public:
        RandomCubeUpdater();
        virtual ~RandomCubeUpdater();

        virtual void prepare();
        virtual void do_update(Ogre::SceneNode* node, Ogre::Entity* entity, uint x, uint y);
    protected:
    private:
};

#endif // RANDOMCUBEUPDATER_H
