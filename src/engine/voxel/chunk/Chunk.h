#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 32

#include "util/CommonIncludes.h"
#include "engine/graphics/VertexData.h"

const int BASE_HEIGHT = 15;
const int DIRT_START = 16;

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

    bool inFrustum(Graphics::Controller *graphics);

    void updateBlockVertexBuffer();

    virtual void intersect(VoxelEntity *ent);
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    Voxel::Manager *m_manager;

    glm::vec3 m_pos;
    int m_blockNumVertices;
    bool m_vertexUpdate;

    BlockPointer m_blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    bool m_visibleMap[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    Graphics::VertexData m_blockVertexBuffer;
    float *m_blockVertexData;
};

#endif // CHUNK_H
