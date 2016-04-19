#ifndef WORLD_H
#define WORLD_H

#include "util/CommonIncludes.h"

#include <QList>

class Graphics;
class Entity;
class PointLight;
class DirectionalLight;
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
    PointLight *getPointLight(int index);
    void addPointLight(PointLight *light);
    void removePointLight(PointLight *light);

    DirectionalLight *getDirectionalLight(int index);
    void addDirectionalLight(DirectionalLight *light);
    void removeDirectionalLight(DirectionalLight *light);

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
    QList<PointLight *> m_pointLights;
    QList<DirectionalLight *> m_directionalLights;

    Camera *m_camera;
};

#endif // SCENE_H
