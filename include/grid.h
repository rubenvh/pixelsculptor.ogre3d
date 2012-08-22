#ifndef GRID_H
#define GRID_H

#include <iostream>
#include "BaseApplication.h"
#include "CubeUpdater.h"
#include "Configuration.h"

class Grid
{
    public:
        Grid(int rows, int cols, int step, int width, int height);
        virtual ~Grid();
        void init(std::string model, std::string material, Ogre::SceneManager* sceneMgr, Ogre::MaterialManager* matMgr);
        unsigned int Getwidth() { return m_width; }
        unsigned int Getheight() { return m_height; }
        void construct();
        void update(CubeUpdater* updater);

    protected:
    private:

        std::string get_cube_entityname(int i, int j);
        std::string get_cube_nodename(int i, int j);

        unsigned int                                    m_rows;
        unsigned int                                    m_cols;
        unsigned int                                    m_width;
        unsigned int                                    m_height;
        unsigned int                                    _step;
        Ogre::SceneManager*                             m_sceneMgr;
        Ogre::MaterialManager*                          m_matMgr;
        std::vector< std::vector<Ogre::SceneNode*> >    _nodes;
        std::vector< std::vector<Ogre::Entity*> >    _entities;

        std::string _model;
        std::string _material;

};

#endif // GRID_H
