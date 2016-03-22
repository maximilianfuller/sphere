#include "engine/manager/Manager.h"

#include "engine/entity/Entity.h"
#include "engine/graphics/Controller.h"

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

void Manager::onDraw(Graphics::Controller *graphics)
{
    foreach(Entity *entity, m_entities)
    {
        entity->onDraw(graphics);
    }
}
