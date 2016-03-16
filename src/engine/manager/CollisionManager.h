#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <QList>

namespace Graphics
{
class Controller;
}
class ActiveEntity;
class BackgroundEntity;

class CollisionManager
{
public:
    CollisionManager(QList<ActiveEntity *> &activeEnts,
                     QList<BackgroundEntity *> &backgroundEnts);

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    QList<ActiveEntity *> &m_activeEntities;
    QList<BackgroundEntity *> &m_backgroundEntities;
};

#endif // COLLISIONMANAGER_H
