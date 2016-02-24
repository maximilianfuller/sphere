#include "BackgroundEntity.h"

BackgroundEntity::BackgroundEntity(World *world) :
    Entity(world)
{
}

BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::onTick(float seconds)
{
    updateShape();
    updateBoundingShape();
}
