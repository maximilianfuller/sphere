#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QList>

namespace Graphics
{
class Controller;
}
class Entity;

class CollisionManager
{
public:
    CollisionManager(QList<Entity *> &entities);

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    QList<Entity *> &m_entities;
};

#endif // COLLISIONMANAGER_H
