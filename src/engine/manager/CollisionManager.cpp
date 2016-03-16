#include "CollisionManager.h"

#include "engine/graphics/Controller.h"
#include "engine/entity/ActiveEntity.h"
#include "engine/entity/BackgroundEntity.h"

CollisionManager::CollisionManager(QList<ActiveEntity *> &activeEnts,
                                   QList<BackgroundEntity *> &backgroundEnts) :
    m_activeEntities(activeEnts),
    m_backgroundEntities(backgroundEnts)
{
}

void CollisionManager::onTick(float seconds)
{
}

void CollisionManager::onDraw(Graphics::Controller *graphics)
{
}
