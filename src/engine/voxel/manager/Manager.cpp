#include "engine/voxel/manager/Manager.h"

#include "engine/voxel/entity/VoxelEntity.h"
#include "engine/voxel/block/Block.h"

Voxel::Manager::Manager()
{
}

Voxel::Manager::~Manager()
{
}

Block *Voxel::Manager::getBlock(BlockPointer p)
{
    return m_blockTypes[p];
}

void Voxel::Manager::onTick(float seconds)
{
    for(int i = 0; i < 4; i++)
    {
        m_chunks[i]->onTick(seconds);
    }

    int numActiveEntities = m_activeEntities.size();

    for(int i = 0; i < numActiveEntities; i++)
    {
        for(int j = 0; j < 4; i++)
        {
            m_chunks[j]->intersect(
                        dynamic_cast<VoxelEntity *>(m_activeEntities[i]));
        }
    }
}

void Voxel::Manager::onDraw(Graphics::Controller *graphics)
{
    /* TODO: load texture atlas */
    for(int i = 0; i < 4; i++)
    {
        m_chunks[i]->onDraw(graphics);
    }
}
