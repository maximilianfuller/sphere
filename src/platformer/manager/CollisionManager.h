#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "engine/manager/Manager.h"

class World;

class CollisionManager : public Manager
{
public:
    CollisionManager(World *world, QList<Entity *> &entities);

    void onTick(float seconds);
};

#endif // COLLISIONMANAGER_H
