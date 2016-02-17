#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 32

#include "util/CommonIncludes.h"

/* Chunk generation constants */
const int BASE_HEIGHT = 16;
const int DIRT_START = 15;

/* Foward declarations */
typedef unsigned char BlockPointer;

namespace Voxel
{
class Manager;
}

namespace Graphics
{
class Controller;
}

class VoxelEntity;
class Terrain;

class Chunk
{
public:
    Chunk(Voxel::Manager *m_manager, Terrain *terrain, glm::vec3 pos);
    virtual ~Chunk();

    void generateBlocks(Terrain *terrain);

    BlockPointer getBlockPointer(int x, int y, int z);
    void setBlockPointer(int x, int y, int z, BlockPointer p);

    glm::vec3 getPosition();

    virtual void intersect(VoxelEntity *ent);
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    Voxel::Manager *m_manager;

    glm::vec3 m_pos;
    BlockPointer m_blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
};

#endif // CHUNK_H
