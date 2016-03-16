#include "engine/voxel/entity/VoxelEntity.h"

#include "engine/intersect/AABoundingBox.h"

#include "engine/voxel/manager/VoxelManager.h"
#include "engine/voxel/block/Block.h"

#include "minecraft/entity/MinecraftPlayer.h"
#include "minecraft/entity/MinecraftEnemy.h"

VoxelEntity::VoxelEntity(VoxelManager *manager, float speed, glm::vec3 pos,
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

    Entity::updateBoundingShape();
}

void VoxelEntity::onIntersect(MinecraftPlayer *ent, glm::vec3 mtv)
{
    return;
}

void VoxelEntity::onIntersect(MinecraftEnemy *ent, glm::vec3 mtv)
{
    return;
}
