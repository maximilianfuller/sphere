#ifndef WORLD_H
#define WORLD_H

#include "util/CommonIncludes.h"

#include <QList>
#include <QString>

class Graphics;
class Entity;
class Camera;
class Manager;

class PointLight;
class DirectionalLight;

class Particle;
class ParticleSystem;

class World
{
public:
    World(Camera *camera);
    virtual ~World();

    /* Camera Management */
    Camera *getCamera();

    /* Entity management */
    int getNumEntities();
    Entity *getEntity(int index);
    QList<Entity *> getEntities();
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

    /* Particle management */
    Particle *getParticle(int index);
    void addParticle(glm::vec3 pos, glm::vec3 vel, float u, float v, QString textureKey);

    /* Game Loop */
    virtual void onTick(float seconds);
    virtual void drawGeometry(Graphics *graphics);
    virtual void drawLights(Graphics *graphics);
    virtual void drawParticles(Graphics *graphics);
    virtual void drawLightGeometry(Graphics *graphics);

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

    QList<Entity *> m_toRemove;

    Particle* m_particles[500];
    int m_particleIndex = 0;

    Camera *m_camera;

private:
    void removeEntities();

};

#endif // SCENE_H
