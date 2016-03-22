#include "CollisionManager.h"

#include "engine/graphics/Controller.h"
#include "engine/entity/Entity.h"

CollisionManager::CollisionManager(QList<Entity *> &entities) :
    m_entities(entities)
{
}

void CollisionManager::onTick(float seconds)
{
}

void CollisionManager::onDraw(Graphics::Controller *graphics)
{
}
