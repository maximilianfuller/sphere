#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include "engine/manager/Manager.h"

class Entity;

class InteractionManager : public Manager
{
public:
    InteractionManager(QList<Entity *> &entities);

    void onTick(float seconds);
};

#endif // INTERACTIONMANAGER_H
