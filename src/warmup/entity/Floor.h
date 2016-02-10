#ifndef FLOOR_H
#define FLOOR_H

#include "engine/entity/Entity.h"

class Floor : public Entity
{
public:
    Floor();
    ~Floor();

    unsigned int getEntityType();
    bool hasIntersection(Entity *ent);
    void intersect(unsigned int e);
    void tick(float seconds);
};

#endif // FLOOR_H
