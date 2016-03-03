#ifndef VOXELENTITY_H
#define VOXELENTITY_H

#include "engine/entity/ActiveEntity.h"

class Manager;
class Block;

class VoxelEntity : public ActiveEntity
{
public:
    VoxelEntity(Manager *manager, float speed = 1.f,
                glm::vec3 pos = glm::vec3(0, 0, 0));
    virtual ~VoxelEntity();
};

#endif // VOXELENTITY_H
