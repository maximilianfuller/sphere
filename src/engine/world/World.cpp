#include "engine/world/World.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/light/Light.h"
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

    foreach(Light *light, m_lights)
    {
        delete(light);
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

Light *World::getLight(int index)
{
    return m_lights[index];
}

void World::addLight(Light *light)
{
    m_lights.append(light);
}

void World::removeLight(Light *light)
{
    int i = 0;

    foreach(Light *l, m_lights)
    {
        if(light == l)
        {
            break;
        }

        i++;
    }

    delete m_lights[i];
    m_lights.removeAt(i);
}

void World::onTick(float seconds)
{
    foreach(Manager *manager, m_managers)
    {
        manager->onTick(seconds);
    }
}

void World::drawGeometry(Graphics *graphics)
{
    foreach(Manager *manager, m_managers)
    {
        manager->onDraw(graphics);
    }
}

void World::drawLights(Graphics *graphics)
{
    foreach(Light *light, m_lights)
    {
        light->draw(graphics);
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
