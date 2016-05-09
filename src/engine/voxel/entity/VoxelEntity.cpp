#include "engine/voxel/entity/VoxelEntity.h"

#include "engine/intersect/AABoundingBox.h"

#include "engine/voxel/manager/VoxelManager.h"
#include "engine/voxel/block/Block.h"

VoxelEntity::VoxelEntity(VoxelManager *manager, float speed, glm::vec3 pos,
                         glm::vec3 dims) :
    m_aabb(new AABoundingBox(pos, dims)),
    Entity(manager, pos, dims, speed)
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

void VoxelEntity::updateShape()
{
    m_aabb->setDimensions(m_dims);
    m_aabb->setPosition(m_pos);

    Entity::updateShape();
}

//void VoxelEntity::onIntersect(MinecraftPlayer *ent, glm::vec3 mtv)
//{
//    return;
//}
//
//void VoxelEntity::onIntersect(MinecraftEnemy *ent, glm::vec3 mtv)
//{
//    return;
//}
