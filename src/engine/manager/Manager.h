#ifndef MANAGER_H
#define MANAGER_H

#include <QList>

class Graphics;
class Entity;

class Manager
{
public:
    Manager(QList<Entity *> &entities);

    virtual void onTick(float seconds);
    virtual void drawGeometry(Graphics *graphics);
    virtual void drawLights(Graphics *graphics);
    virtual void drawParticles(Graphics *graphics);

protected:
    QList<Entity *> &m_entities;
};

#endif // MANAGER_H
