#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QList>

class Graphics;
class Entity;

class CollisionManager
{
public:
    CollisionManager(QList<Entity *> &entities);

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics *graphics);

protected:
    QList<Entity *> &m_entities;
};

#endif // COLLISIONMANAGER_H
