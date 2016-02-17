#include "engine/voxel/chunk/Chunk.h"

#include "engine/voxel/entity/VoxelEntity.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/terrain/Terrain.h"
#include "engine/voxel/block/Block.h"

/* TODO: generate all block faces using graphics controller */
/* TODO: set up blocks */

Chunk::Chunk(Voxel::Manager *manager, Terrain *terrain, glm::vec3 pos) :
    m_manager(manager),
    m_pos(pos)
{
    generateBlocks(terrain);
}

Chunk::~Chunk()
{
}

void Chunk::generateBlocks(Terrain *terrain)
{
    float height;

    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            for(int y = 0; y < CHUNK_SIZE; y++)
            {
                height = terrain->getHeight(x, z) + BASE_HEIGHT;

                if(y > height)
                {
                    setBlockPointer(x, y, z, BLOCK_AIR);
                }
                else if (y == height)
                {
                    setBlockPointer(x, y, z, BLOCK_GRASS);
                }
                else if(y >= DIRT_START)
                {
                    setBlockPointer(x, y, z, BLOCK_DIRT);
                }
                else
                {
                    setBlockPointer(x, y, z, BLOCK_ROCK);
                }
            }
        }
    }
}

BlockPointer Chunk::getBlockPointer(int x, int y, int z)
{
    return m_blocks[y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x];
}

void Chunk::setBlockPointer(int x, int y, int z, BlockPointer p)
{
    m_blocks[y * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + x] = p;
}

glm::vec3 Chunk::getPosition()
{
    return m_pos;
}

// NOTE: should blocks be entities? should chunks be entities?
void Chunk::intersect(VoxelEntity *ent)
{
    Block *block;

    int blockIndex = 0;

    for(int y = 0; y < CHUNK_SIZE; y++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            for(int x = 0; x < CHUNK_SIZE; x++)
            {
                block = m_manager->getBlock(m_blocks[blockIndex]);

                if(ent->intersect(block, m_pos + glm::vec3(x, y, z)))
                {
                    /* TODO (later): chunk callbacks, block pointer updating */
                }

                blockIndex++;
            }
        }
    }
}

void Chunk::onTick(float seconds)
{
}

void Chunk::onDraw(Graphics::Controller *graphics)
{
    Block *block;

    int blockIndex = 0;

    for(int y = 0; y < CHUNK_SIZE; y++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            for(int x = 0; x < CHUNK_SIZE; x++)
            {
                block = m_manager->getBlock(m_blocks[blockIndex]);
                block->onDraw(graphics, m_manager, this, x, y, z);
            }
        }
    }
}
