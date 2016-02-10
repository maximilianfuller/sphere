#ifndef BACKGROUNDENTITY_H
#define BACKGROUNDENTITY_H

#include "engine/entity/Entity.h"

class BackgroundEntity : public Entity
{
public:
    BackgroundEntity();
    ~BackgroundEntity();

    virtual EntityType getEntityType() const;

    virtual void onTick(float seconds);
};

#endif // BACKGROUNDENTITY_H
