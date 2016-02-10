#ifndef SCENE_H
#define SCENE_H

#include "util/CommonIncludes.h"
#include <QList>

namespace Graphics
{
class Controller;
}
class Entity;

class World
{
public:
    World();
    virtual ~World();

    /* Entity management */
    int getNumEntities();
    Entity *getEntity(int index);
    void addEntity(Entity *ent);
    void removeEntity(Entity *ent);

    /* Game Loop */
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

    /* Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    QList<Entity *> m_entities;
};

#endif // SCENE_H
