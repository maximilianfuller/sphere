#include "warmup/entity/WarmupEntity.h"

#include "engine/world/World.h"

#include "warmup/entity/Floor.h"
#include "warmup/entity/Player.h"
#include "warmup/entity/Zombie.h"
#include "warmup/entity/Bomb.h"

WarmupEntity::WarmupEntity(World *world) :
    Entity(world)
{
}

WarmupEntity::~WarmupEntity()
{
}

void WarmupEntity::onIntersect(Player *player, glm::vec3 mtv)
{
    return;
}

void WarmupEntity::onIntersect(Floor *floor, glm::vec3 mtv)
{
    return;
}

void WarmupEntity::onIntersect(Zombie *zombie, glm::vec3 mtv)
{
    return;
}

void WarmupEntity::onIntersect(Bomb *bomb, glm::vec3 mtv)
{
    return;
}
