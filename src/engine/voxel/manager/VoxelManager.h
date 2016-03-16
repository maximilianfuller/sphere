#ifndef MANAGER_H
#define MANAGER_H

#include "engine/world/World.h"

#include "engine/voxel/chunk/Chunk.h"

#include <QList>
#include <QQueue>

typedef unsigned char BlockPointer;

class Block;
class Terrain;
class VoxelCollisionManager;
class CylinderCollisionManager;
class VoxelEntity;
class Camera;
class Quad;

enum SelectedFace {
    LeftFace,
    RightFace,
    BottomFace,
    TopFace,
    BackFace,
    FrontFace,
    NoneFace
};

class VoxelManager : public World
{
public:
    VoxelManager(Camera *camera, Terrain *terrain);
    virtual ~VoxelManager();

    Block *getBlock(BlockPointer p);
    VoxelEntity *getPlayer();

    /* Chunk streaming */
    void purgeChunks();
    void loadChunks();

    /* Raycasting */
    Chunk *getChunk(float x, float y, float z);
    void castRay(glm::vec3 p, glm::vec3 d);
    void selectBlock(int x, int y, int z, glm::vec3 p, glm::vec3 d, float t);
    void renderSelectedBlock(Graphics::Controller *graphics);

    /* Game loop */
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    /* Blocks and chunks */
    Block *m_blocks[256];

    Terrain *m_terrain;
    QList<Chunk *> m_chunks;
    QQueue<Chunk *> m_chunkQueue;
    int m_chunkRadius = 2;

    /* Selection rendering */
    SelectedFace m_selectedFace;
    glm::vec3 m_selectedPos;

    float m_lastT;
    float m_maxT = 8.0;

    Quad *m_face;

    /* Entities */
    VoxelCollisionManager *m_voxelManager;
    CylinderCollisionManager *m_cylinderManager;
    VoxelEntity *m_player;
};

#endif // MANAGER_H
