#ifndef MANAGER_H
#define MANAGER_H

#include <QList>

class Graphics;
class Entity;
class World;

class Manager
{
public:
    Manager(World *world, QList<Entity *> &entities);

    virtual void onTick(float seconds);
    virtual void drawGeometry(Graphics *graphics);
    virtual void drawLights(Graphics *graphics);
    virtual void drawParticles(Graphics *graphics);
    virtual void drawLightGeometry(Graphics *graphics);

protected:
    QList<Entity *> &m_entities;
    World *m_world;
};

#endif // MANAGER_H
