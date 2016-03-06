#include "engine/voxel/entity/VoxelEntity.h"

#include "engine/intersect/AABoundingBox.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/block/Block.h"

VoxelEntity::VoxelEntity(Manager *manager, float speed, glm::vec3 pos,
                         glm::vec3 dims) :
    m_aabb(new AABoundingBox(pos, dims)),
    ActiveEntity(manager, speed),
    Entity(manager, pos)
{
}

VoxelEntity::~VoxelEntity()
{
    delete m_aabb;
}

AABoundingBox *VoxelEntity::getAABB()
{
    return m_aabb;
}

void VoxelEntity::updateBoundingShape()
{
    m_aabb->setDimensions(m_dims);
    m_aabb->setPosition(m_pos);
}
