#ifndef VOXELENTITY_H
#define VOXELENTITY_H

#include "engine/entity/ActiveEntity.h"

class Manager;
class AABoundingBox;

class VoxelEntity : public ActiveEntity
{
public:
    VoxelEntity(Manager *manager, float speed = 1.f,
                glm::vec3 pos = glm::vec3(0, 0, 0),
                glm::vec3 dims = glm::vec3(1, 1, 1));
    virtual ~VoxelEntity();

    AABoundingBox *getAABB();

    void updateBoundingShape();

protected:
    AABoundingBox *m_aabb;
};

#endif // VOXELENTITY_H
