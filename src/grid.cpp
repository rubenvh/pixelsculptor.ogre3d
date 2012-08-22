#include "../include/grid.h"

using namespace std;

Grid::Grid(int rows, int cols, int step, int width, int height):
    m_rows(rows), m_cols(cols),
    m_width(width), m_height(height), _step(step),
    _nodes(cols, std::vector<Ogre::SceneNode*>(rows)),
    _entities(cols, std::vector<Ogre::Entity*>(rows))
{

}

Grid::~Grid()
{
}

void Grid::init(std::string model, std::string material, Ogre::SceneManager* sceneMgr, Ogre::MaterialManager* matMgr)
{
    _model = model;
    _material = material;
    m_sceneMgr = sceneMgr;
    m_matMgr = matMgr;
}

void Grid::construct()
{
    Ogre::Entity* cube;
    Ogre::SceneNode* cubeNode;

    // load entity & attach entity to scene node
    for (uint i = 0; i < m_cols; i++)
    {
        for (uint j= 0; j <m_rows; j++)
        {
            std::string cubeName(get_cube_entityname(i, j));
            std::string cubeNodeName(get_cube_nodename(i,j));

            cube = m_sceneMgr->createEntity(cubeName, _model);

            Ogre::MaterialPtr base_material = m_matMgr->getByName(_material);
            Ogre::MaterialPtr mMat = base_material->clone("Material_"+cubeName);
            mMat->setReceiveShadows(true);
            cube->setMaterialName("Material_"+cubeName);
            cube->setCastShadows(true);

            int height = cube->getBoundingBox().getSize().y / 2;
            int x = (int)(i*_step - m_cols*_step*1.0/2.0);
            int y = (int)(j*_step - m_rows*_step*1.0/2.0);
            cout << "Initialized cube for column " << i << " and row " << j << endl;
            cout << "\t(x, y) = (" << x << ", " << y <<")"<<endl;

            cubeNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode(cubeNodeName, Ogre::Vector3( x, height, y));
            cubeNode->attachObject(cube );

            // store node locally, preventing lookup in scenemanager
            _nodes[i][j]=cubeNode;
            _entities[i][j]=cube;
        }
    }
}

void Grid::update(CubeUpdater* updater)
{
    Ogre::SceneNode* cubeNode;
    Ogre::Entity* entity;

    for (uint i = 0; i < m_cols; i++)
    {
        for (uint j= 0; j <m_rows; j++)
        {
            cubeNode = _nodes[i][j];
            entity = _entities[i][j];

            if (cubeNode != 0)
            {
                updater->do_update(cubeNode, entity, i, j);
            }
        }
    }
}

std::string Grid::get_cube_entityname(int i, int j)
{
    std::stringstream cubeName;
    cubeName << "cube_"<<i<<"_"<<j;
    return cubeName.str();
}

std::string Grid::get_cube_nodename(int i, int j)
{
    std::stringstream cubeName;
    cubeName << "cube_"<<i<<"_"<<j<<"_node";
    return cubeName.str();
}
