#ifndef WORLD_H
#define WORLD_H

#include "util/CommonIncludes.h"

#include <QList>

namespace Graphics
{
class Controller;
}
class Entity;
class Camera;
class Manager;

class World
{
public:
    World(Camera *camera);
    virtual ~World();

    /* Entity management */
    int getNumEntities();
    Entity *getEntity(int index);
    void addEntity(Entity *ent);
    void removeEntity(Entity *ent);

    /* Manager management */
    void addManager(Manager *manager);

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

protected:
    QList<Manager *> m_managers;
    QList<Entity *> m_entities;

    Camera *m_camera;
};

#endif // SCENE_H
