#ifndef WORLD_H
#define WORLD_H

#include "util/CommonIncludes.h"

#include <QList>

class Graphics;
class Entity;
class Light;
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

    /* Light management */
    Light *getLight(int index);
    void addLight(Light *light);
    void removeLight(Light *light);

    /* Game Loop */
    virtual void onTick(float seconds);
    virtual void drawGeometry(Graphics *graphics);
    virtual void drawLights(Graphics *graphics);

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
    QList<Light *> m_lights;

    Camera *m_camera;
};

#endif // SCENE_H
