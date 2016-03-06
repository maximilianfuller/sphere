#ifndef BLOCK_H
#define BLOCK_H

#include "engine/entity/Entity.h"

#include "engine/graphics/Controller.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/chunk/Chunk.h"
#include "engine/voxel/shape/VoxelCube.h"

const BlockPointer BLOCK_AIR = 0;
const BlockPointer BLOCK_GRASS = 1;
const BlockPointer BLOCK_DIRT = 2;
const BlockPointer BLOCK_ROCK = 3;

struct Block
{
public:
    Block(char p, VoxelCube *cube) :
        passable(p),
        m_cube(cube)
    {
    }

    ~Block()
    {
        delete m_cube;
    }

    void onDraw(float *vertexData, int &numVertices, glm::vec3 blockPos,
                bool drawLeft, bool drawRight, bool drawBack, bool drawFront,
                bool drawBot, bool drawTop)
    {
        m_cube->setPosition(blockPos);
        m_cube->draw(vertexData, numVertices, drawLeft, drawRight,
                     drawBot, drawTop, drawBack, drawFront);
    }

    char passable;

private:
    VoxelCube *m_cube;

} __attribute((packed));

#endif // BLOCK_H
