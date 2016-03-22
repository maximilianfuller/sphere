#ifndef CYLINDERCOLLISIONMANAGER_H
#define CYLINDERCOLLISIONMANAGER_H

#include "engine/manager/Manager.h"

class Entity;

class CylinderCollisionManager : public Manager
{
public:
    CylinderCollisionManager(QList<Entity *> &entities);

    void intersect(Entity *e1, Entity *e2);

    virtual void onTick(float seconds);
};

#endif // CYLINDERCOLLISIONMANAGER_H
