#ifndef VOXELENTITY_H
#define VOXELENTITY_H

#include "engine/entity/ActiveEntity.h"

namespace Voxel
{
class Manager;
}
class Block;

class VoxelEntity : public ActiveEntity
{
public:
    VoxelEntity(Voxel::Manager *manager, float speed = 1.f,
                glm::vec3 pos = glm::vec3(0, 0, 0));
    virtual ~VoxelEntity();

    virtual bool intersect(Block *block, glm::vec3 blockPos);
    virtual void onIntersect(Block *block, glm::vec3 mtv);
};

#endif // VOXELENTITY_H
