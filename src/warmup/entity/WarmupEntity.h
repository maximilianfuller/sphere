#ifndef WARMUPENTITY_H
#define WARMUPENTITY_H

#include "engine/entity/Entity.h"

class Player;
class Floor;
class Zombie;
class Bomb;

class WarmupEntity : public virtual Entity
{
public:
    WarmupEntity(World *world);
    virtual ~WarmupEntity();

    virtual void onIntersect(Player *player, glm::vec3 mtv);
    virtual void onIntersect(Floor *floor, glm::vec3 mtv);
    virtual void onIntersect(Zombie *zombie, glm::vec3 mtv);
    virtual void onIntersect(Bomb *bomb, glm::vec3 mtv);
};

#endif // WARMUPENTITY_H
