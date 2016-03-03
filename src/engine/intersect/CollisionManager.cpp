#include "CollisionManager.h"

#include "engine/entity/ActiveEntity.h"
#include "engine/entity/BackgroundEntity.h"

/* TODO: implement cylinder collision manager */
/* TODO: remove collision test functionality from bounding shapes */
/* TODO: make collision shapes with dimensions */
CollisionManager::CollisionManager(QList<ActiveEntity *> &activeEnts,
                                   QList<BackgroundEntity *> &backgroundEnts) :
    m_activeEntities(activeEnts),
    m_backgroundEntities(backgroundEnts)
{
}

void CollisionManager::onTick(float seconds)
{

}

void CollisionManager::onDraw()
{

}
