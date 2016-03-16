#ifndef CYLINDERCOLLISIONMANAGER_H
#define CYLINDERCOLLISIONMANAGER_H

#include "engine/manager/CollisionManager.h"

class Entity;

class CylinderCollisionManager : public CollisionManager
{
public:
    CylinderCollisionManager(QList<ActiveEntity *> &activeEnts,
                             QList<BackgroundEntity *> &backgroundEnts);

    void intersect(Entity *e1, Entity *e2);

    virtual void onTick(float seconds);
};

#endif // CYLINDERCOLLISIONMANAGER_H
