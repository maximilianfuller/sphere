#ifndef FLOOR_H
#define FLOOR_H

#include "engine/entity/BackgroundEntity.h"
#include "warmup/entity/WarmupEntity.h"

class World;

class Floor : public BackgroundEntity, public WarmupEntity
{
public:
    Floor(World *world);
    ~Floor();

    void onIntersect(Entity *ent, glm::vec3 mtv);
};

#endif // FLOOR_H
