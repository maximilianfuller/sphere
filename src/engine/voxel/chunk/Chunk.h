#ifndef CHUNK_H
#define CHUNK_H

#include "util/CommonIncludes.h"
#include "engine/graphics/VertexData.h"

const int CHUNK_SIZE = 32;
const int BASE_HEIGHT = 35;
const int DIRT_START = 30;

typedef unsigned char BlockPointer;

class VoxelManager;
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
    Chunk(VoxelManager *manager, glm::vec3 pos);
    virtual ~Chunk();

    /* Accessor methods */
    BlockPointer getBlockPointer(int x, int y, int z);
    void setBlockPointer(int x, int y, int z, BlockPointer p);

    glm::vec3 getPosition();

    AABoundingBox *getAABB();

    bool passable(int x, int y, int z);
    bool inChunk(int x, int y, int z);

    /* Chunk generation methods */
    void generateBlocks(Terrain *terrain);
    void updateBlockVertexBuffer();

    /* Game loop */
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    VoxelManager *m_manager;

    glm::vec3 m_pos;
    AABoundingBox *m_aabb;

    BlockPointer m_blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    bool m_passableMap[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    Graphics::VertexData m_vertexBuffer;
    float *m_vertexData;
};

#endif // CHUNK_H
