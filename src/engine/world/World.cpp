#include "engine/world/World.h"

#include "engine/entity/ActiveEntity.h"
#include "engine/entity/BackgroundEntity.h"
#include "engine/graphics/Controller.h"
#include "engine/camera/Camera.h"

World::World(Camera *camera) :
    m_camera(camera)
{
}

World::~World()
{
    QList<ActiveEntity *>::iterator a;

    for(a = m_activeEntities.begin(); a != m_activeEntities.end(); a++)
    {
        delete (*a);
    }

    QList<BackgroundEntity *>::iterator b;

    for(b = m_backgroundEntities.begin(); b != m_backgroundEntities.end(); b++)
    {
        delete (*b);
    }
}

int World::getNumActiveEntities()
{
    return m_activeEntities.size();
}

ActiveEntity *World::getActiveEntity(int index)
{
    return m_activeEntities[index];
}

void World::addActiveEntity(ActiveEntity *ent)
{
    m_activeEntities.append(ent);
}

void World::removeActiveEntity(ActiveEntity *ent)
{
    QList<ActiveEntity *>::iterator a;
    int i = 0;

    for(a = m_activeEntities.begin(); a != m_activeEntities.end(); a++)
    {
        if(*a == ent)
            break;

        i++;
    }

    delete m_activeEntities[i];
    m_activeEntities.removeAt(i);
}

int World::getNumBackgroundEntities()
{
    return m_backgroundEntities.size();
}

BackgroundEntity *World::getBackgroundEntity(int index)
{
    return m_backgroundEntities[index];
}

void World::addBackgroundEntity(BackgroundEntity *ent)
{
    m_backgroundEntities.append(ent);
}

void World::removeBackgroundEntity(BackgroundEntity *ent)
{
    QList<BackgroundEntity *>::iterator b;
    int i = 0;

    for(b = m_backgroundEntities.begin(); b != m_backgroundEntities.end(); b++)
    {
        if(*b == ent)
            break;

        i++;
    }

    delete m_backgroundEntities[i];
    m_backgroundEntities.removeAt(i);
}

void World::onTick(float seconds)
{
    foreach(ActiveEntity *ent, m_activeEntities)
    {
        ent->onTick(seconds);
    }

    foreach(BackgroundEntity *ent, m_backgroundEntities)
    {
        ent->onTick(seconds);
    }
}

void World::onDraw(Graphics::Controller *graphics)
{
    foreach(ActiveEntity *ent, m_activeEntities)
    {
        ent->onDraw(graphics);
    }

    foreach(BackgroundEntity *ent, m_backgroundEntities)
    {
        ent->onDraw(graphics);
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
