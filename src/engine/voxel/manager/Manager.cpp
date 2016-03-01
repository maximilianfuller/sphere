#include "engine/voxel/manager/Manager.h"

#include "engine/voxel/entity/VoxelEntity.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/terrain/Terrain.h"

Voxel::Manager::Manager(Terrain *terrain, QString atlasKey) :
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
}

Voxel::Manager::~Manager()
{
    for(int i = 0; i < NUM_CHUNKS; i++)
    {
        delete m_chunks[i];
    }

    delete m_terrain;
}

Block *Voxel::Manager::getBlock(BlockPointer p)
{
    return m_blockTypes[p];
}

void Voxel::Manager::onTick(float seconds)
{
    for(int i = 0; i < NUM_CHUNKS; i++)
    {
        m_chunks[i]->onTick(seconds);
    }

    int numActiveEntities = m_activeEntities.size();

    for(int i = 0; i < numActiveEntities; i++)
    {
        for(int j = 0; j < NUM_CHUNKS; j++)
        {
            m_chunks[j]->intersect(
                        dynamic_cast<VoxelEntity *>(m_activeEntities[i]));
        }
    }

    World::onTick(seconds);
}

void Voxel::Manager::onDraw(Graphics::Controller *graphics)
{
    World::onDraw(graphics);

    graphics->loadTexture(m_atlasKey, GL_TEXTURE0);

    for(int i = 0; i < NUM_CHUNKS; i++)
    {
        m_chunks[i]->onDraw(graphics);
    }

    graphics->unloadTexture(GL_TEXTURE0);
}
