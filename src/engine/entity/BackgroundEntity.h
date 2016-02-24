#ifndef BACKGROUNDENTITY_H
#define BACKGROUNDENTITY_H

#include "engine/entity/Entity.h"

class World;

class BackgroundEntity : public virtual Entity
{
public:
    BackgroundEntity(World *world);
    ~BackgroundEntity();

    virtual void onTick(float seconds);
};

#endif // BACKGROUNDENTITY_H
