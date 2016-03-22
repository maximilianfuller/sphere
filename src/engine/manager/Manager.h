#ifndef MANAGER_H
#define MANAGER_H

#include <QList>

namespace Graphics
{
class Controller;
}
class Entity;

class Manager
{
public:
    Manager(QList<Entity *> &entities);

    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    QList<Entity *> &m_entities;
};

#endif // MANAGER_H
