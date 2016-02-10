#include "engine/world/World.h"

#include "engine/entity/Entity.h"
#include "engine/graphics/Controller.h"

World::World()
{
}

World::~World()
{
    QList<Entity *>::iterator e;

    for(e = m_entities.begin(); e != m_entities.end(); e++)
    {
        delete (*e);
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
    QList<Entity *>::iterator e;
    int i = 0;

    for(e = m_entities.begin(); e != m_entities.end(); e++)
    {
        if(*e == ent)
            break;

        i++;
    }

    delete m_entities[i];
    m_entities.removeAt(i);
}

void World::tick(float seconds)
{
    int numEntities = m_entities.size();

    // Tick entities
    // Iterate backwards to avoid unexpected behavior
    for(int i = numEntities - 1; i >= 0; i--)
    {
        m_entities[i]->tick(seconds);
    }

    // Intersect entities
    for(int i = 0; i < numEntities; i++)
    {
        for(int j = i + 1; j < numEntities; j++)
        {
            intersect(m_entities[i], m_entities[j]);
        }
    }
}

void World::intersect(Entity *e1, Entity *e2)
{
    // Approach 1: intersector namespace, with different intersect methods for different bounding shapes (or entities)
    // Approach 2: intersect methods for each entity. Have to be written on the engine side.
    // Approach 2 would mean that every entity would need an intersect method for every other entity (there would be twice as many) methods,
    // with lots of repeated code.

    // TODO: set up different types of bounding shapes
    // TODO: Check intersection with bounding shapes
    // TODO: Get minimum translation vector with bounding boxes
    // TODO: Resolve the intersection by translating along mtvs
    // TODO: Call callbacks
}

void World::draw(Graphics::Controller *graphics)
{
    QList<Entity *>::iterator e;
    int count = 0;

    for(e = m_entities.begin(); e != m_entities.end(); e++)
    {
        (*e)->draw(graphics);
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
