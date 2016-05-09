#ifndef VOXELENTITY_H
#define VOXELENTITY_H

#include "engine/entity/Entity.h"

class VoxelManager;
class AABoundingBox;

class MinecraftPlayer;
class MinecraftEnemy;

class VoxelEntity : public Entity
{
public:
    VoxelEntity(VoxelManager *manager, float speed = 1.f,
                glm::vec3 pos = glm::vec3(0, 0, 0),
                glm::vec3 dims = glm::vec3(1, 1, 1));
    virtual ~VoxelEntity();

    /* Accessors */
    AABoundingBox *getAABB();

    void updateShape();

    /* Intersect methods */
    //virtual void onIntersect(MinecraftPlayer *ent, glm::vec3 mtv);
    //virtual void onIntersect(MinecraftEnemy *ent, glm::vec3 mtv);

protected:
    AABoundingBox *m_aabb;
};

#endif // VOXELENTITY_H
