#include "engine/voxel/entity/VoxelEntity.h"

#include "engine/intersect/BoundingShape.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/voxel/block/Block.h"

VoxelEntity::VoxelEntity(Manager *manager, float speed, glm::vec3 pos) :
    Entity(manager, pos),
    ActiveEntity(manager, speed, pos)
{
}

VoxelEntity::~VoxelEntity()
{
}
