#include "engine/world/World.h"

#include "engine/graphics/Controller.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/manager/Manager.h"

World::World(Camera *camera) :
    m_camera(camera)
{
}

World::~World()
{
    foreach(Entity *ent, m_entities)
    {
        delete(ent);
    }

    foreach(Manager *manager, m_managers)
    {
        delete(manager);
    }
}

int World::getNumEntities()
{
    return m_entities.size();
}

Entity *World::getEntity(int index)
{
    return m_entities[index];
}

void World::addEntity(Entity *ent)
{
    m_entities.append(ent);
}

void World::removeEntity(Entity *ent)
{
    int i = 0;

    foreach(Entity *e, m_entities)
    {
        if(ent == e)
        {
            break;
        }

        i++;
    }

    delete m_entities[i];
    m_entities.removeAt(i);
}

void World::addManager(Manager *manager)
{
    m_managers.append(manager);
}

void World::onTick(float seconds)
{
    foreach(Manager *manager, m_managers)
    {
        manager->onTick(seconds);
    }
}

void World::onDraw(Graphics::Controller *graphics)
{
    foreach(Manager *manager, m_managers)
    {
        manager->onDraw(graphics);
    }
}

void World::mousePressEvent(QMouseEvent *event)
{
}

void World::mouseMoveEvent(QMouseEvent *event, int startX,
                           int startY)
{
}

void World::mouseReleaseEvent(QMouseEvent *event)
{
}

void World::wheelEvent(QWheelEvent *event)
{
}

void World::keyPressEvent(QKeyEvent *event)
{
}

void World::keyReleaseEvent(QKeyEvent *event)
{
}
