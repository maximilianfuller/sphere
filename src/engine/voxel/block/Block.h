#ifndef BLOCK_H
#define BLOCK_H

#include "engine/entity/Entity.h"

#include "engine/graphics/Controller.h"
#include "engine/intersect/BoundingBox.h"

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
        m_cube(cube),
        m_boundingBox(new BoundingBox())
    {
    }

    ~Block()
    {
        delete m_cube;
        delete m_boundingBox;
    }

    void onDraw(float *vertexData, int &numVertices, glm::vec3 blockPos,
                bool drawLeft, bool drawRight, bool drawBack, bool drawFront,
                bool drawBot, bool drawTop)
    {
        m_cube->setPosition(blockPos);
        m_cube->draw(vertexData, numVertices, drawLeft, drawRight,
                     drawBot, drawTop, drawBack, drawFront);
    }

    BoundingBox *getBoundingBox(glm::vec3 blockPos)
    {
        m_boundingBox->setPosition(blockPos);
        return m_boundingBox;
    }

    char passable;

private:
    VoxelCube *m_cube;
    BoundingBox *m_boundingBox;

} __attribute((packed));

#endif // BLOCK_H
