#include "engine/voxel/manager/Manager.h"

#include "engine/voxel/entity/VoxelEntity.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/intersect/VoxelCollisionManager.h"

Manager::Manager(Terrain *terrain, QString atlasKey) :
    m_terrain(terrain),
    m_atlasKey(atlasKey)
{
    int chunkIndex = 0;

    for(int y = 0; y < CHUNKS_HEIGHT; y++)
    {
        for(int x = 0; x < CHUNKS_WIDTH; x++)
        {
            for(int z = 0; z < CHUNKS_WIDTH; z++)
            {
                m_chunks[chunkIndex++] = new Chunk(this, m_terrain,
                                                   glm::vec3(CHUNK_SIZE * x, CHUNK_SIZE * y, CHUNK_SIZE * z));
            }
        }
    }

    m_cmanager = new VoxelCollisionManager(m_chunks, NUM_CHUNKS, m_activeEntities, m_backgroundEntities);
}

Manager::~Manager()
{
    for(int i = 0; i < NUM_CHUNKS; i++)
    {
        delete m_chunks[i];
    }

    delete m_terrain;

    delete m_cmanager;
}

Block *Manager::getBlock(BlockPointer p)
{
    return m_blockTypes[p];
}

void Manager::onTick(float seconds)
{
    m_cmanager->onTick(seconds);

    int numActiveEntities = m_activeEntities.size();

    for(int i = 0; i < numEntities; i++)
    {
        m_activeEntities[i]->onTick(seconds);
    }
}

void Manager::onDraw(Graphics::Controller *graphics)
{
    World::onDraw(graphics);

    graphics->sendColorUniform(glm::vec3(0.5, 0.5, 0.5), "default");
    graphics->sendUseTextureUniform(1, "default");
    graphics->sendModelUniform(glm::mat4x4(), "default");

    for(int i = 0; i < NUM_CHUNKS; i++)
    {
        m_chunks[i]->onDraw(graphics);
    }
}
