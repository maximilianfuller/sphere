#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 32

#include "util/CommonIncludes.h"
#include "engine/graphics/VertexData.h"

const int BASE_HEIGHT = 35;
const int DIRT_START = 30;

typedef unsigned char BlockPointer;

class Manager;
namespace Graphics
{
class Controller;
}
class AABoundingBox;

class VoxelEntity;
class Terrain;

class Chunk
{
public:
    Chunk(Manager *m_manager, glm::vec3 pos);
    virtual ~Chunk();

    BlockPointer getBlockPointer(int x, int y, int z);
    void setBlockPointer(int x, int y, int z, BlockPointer p);

    glm::vec3 getPosition();

    AABoundingBox *getAABB();

    void generateBlocks(Terrain *terrain);
    bool updateBlockVertexBuffer();

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    Manager *m_manager;

    glm::vec3 m_pos;
    AABoundingBox *m_aabb;

    BlockPointer m_blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    bool m_visibleMap[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    bool m_vertexUpdate;
    Graphics::VertexData m_blockVertexBuffer;
    float *m_blockVertexData;

    int m_lastY, m_numVertices;
    bool m_generated;
};

#endif // CHUNK_H
