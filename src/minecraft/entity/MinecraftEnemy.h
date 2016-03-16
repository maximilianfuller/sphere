#ifndef MINECRAFTENEMY_H
#define MINECRAFTENEMY_H

#include "engine/voxel/entity/VoxelEntity.h"

class MinecraftManager;

class MinecraftEnemy : public VoxelEntity
{
public:
    MinecraftEnemy(MinecraftManager *manager, glm::vec3 pos);
    ~MinecraftEnemy();

    void jump();
    void updateFriction();
    void updateGoalVelocity();
    void updateAcceleration();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);
    void onIntersect(MinecraftPlayer *ent, glm::vec3 mtv);
    void onIntersect(MinecraftEnemy *ent, glm::vec3 mtv);

    void onTick(float seconds);

protected:
    bool m_jump;
};

#endif // MINECRAFTENEMY_H
