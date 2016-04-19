#include "engine/world/World.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/light/PointLight.h"
#include "engine/light/DirectionalLight.h"
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

    foreach(PointLight *light, m_pointLights)
    {
        delete(light);
    }

    foreach(DirectionalLight *light, m_directionalLights)
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

PointLight *World::getPointLight(int index)
{
    return m_pointLights[index];
}

void World::addPointLight(PointLight *light)
{
    m_pointLights.append(light);
}

void World::removePointLight(PointLight *light)
{
    int i = 0;

    foreach(PointLight *l, m_pointLights)
    {
        if(light == l)
        {
            break;
        }

        i++;
    }

    delete m_pointLights[i];
    m_pointLights.removeAt(i);
}

DirectionalLight *World::getDirectionalLight(int index)
{
    return m_directionalLights[index];
}

void World::addDirectionalLight(DirectionalLight *light)
{
    m_directionalLights.append(light);
}

void World::removeDirectionalLight(DirectionalLight *light)
{
    int i = 0;

    foreach(DirectionalLight *l, m_directionalLights)
    {
        if(light == l)
        {
            break;
        }

        i++;
    }

    delete m_directionalLights[i];
    m_directionalLights.removeAt(i);
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
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    foreach(Manager *manager, m_managers)
    {
        manager->onDraw(graphics);
    }
}

void World::drawLights(Graphics *graphics)
{
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    foreach(PointLight *light, m_pointLights)
    {
        light->draw(graphics);
    }

    graphics->sendEmptyMatrices();

    foreach(DirectionalLight *light, m_directionalLights)
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
