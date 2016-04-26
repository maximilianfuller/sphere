#include "engine/manager/Manager.h"

#include "engine/entity/Entity.h"
#include "engine/graphics/Graphics.h"
#include "engine/world/World.h"

Manager::Manager(QList<Entity *> &entities) :
    m_entities(entities)
{
}

void Manager::onTick(float seconds)
{
    foreach(Entity *entity, m_entities)
    {
        entity->onTick(seconds);
    }
}

void Manager::drawGeometry(Graphics *graphics)
{
    foreach(Entity *entity, m_entities)
    {
        entity->drawGeometry(graphics);
    }
}

void Manager::drawLights(Graphics *graphics)
{
    foreach(Entity *entity, m_entities)
    {
        entity->drawLights(graphics);
    }
}

void Manager::drawParticles(Graphics *graphics)
{
    foreach(Entity *entity, m_entities)
    {
        entity->drawParticles(graphics);
    }
}

void Manager::getLightGeometry(Graphics *graphics,
                               std::priority_queue<std::pair<PointLight *,float>,
                                   std::vector<std::pair<PointLight *,float> >,
                                   CompareDepth> &depthQueue)
{
    foreach(Entity *entity, m_entities)
    {
        entity->getLightGeometry(graphics, depthQueue);
    }
}
