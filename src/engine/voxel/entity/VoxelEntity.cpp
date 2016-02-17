#include "engine/voxel/entity/VoxelEntity.h"

#include "engine/intersect/BoundingShape.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/block/Block.h"

VoxelEntity::VoxelEntity(Voxel::Manager *manager, float speed, glm::vec3 pos) :
    Entity(manager, pos),
    ActiveEntity(manager, speed, pos)
{
}

VoxelEntity::~VoxelEntity()
{
}

bool VoxelEntity::intersect(Block *block, glm::vec3 blockPos)
{
    glm::vec3 mtv;

    if(m_boundingShape->intersect(block->getBoundingBox(blockPos), mtv))
    {
        onIntersect(block, mtv);

        return true;
    }

    return false;
}

void VoxelEntity::onIntersect(Block *block, glm::vec3 mtv)
{
    return;
}
