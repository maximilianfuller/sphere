#include "BackgroundEntity.h"

BackgroundEntity::BackgroundEntity()
{
}

BackgroundEntity::~BackgroundEntity()
{
}

EntityType BackgroundEntity::getEntityType() const
{
    return ActiveType;
}

void BackgroundEntity::onTick(float seconds)
{
}
