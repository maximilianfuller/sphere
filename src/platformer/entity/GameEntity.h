#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "engine/entity/Entity.h"

class Graphics;
class Camera;
class World;

class PointLight;
class ParticleStreamSystem;

class GameEntity : public Entity
{
public:
    GameEntity(World *world, Camera *camera,
               glm::vec3 pos = glm::vec3(0, 0, 0),
               glm::vec3 dims = glm::vec3(1, 1, 1),
               float speed = 1,
               glm::vec3 vel = glm::vec3(0, 0, 0),
               glm::vec3 acc = glm::vec3(0, G, 0),
               glm::vec3 goal = glm::vec3(0, 0, 0),
               float friction = MU_GROUND);
    virtual ~GameEntity();

    /* Particles */
    void startParticles();
    void stopParticles();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);

    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
    void drawLights(Graphics *graphics);
    void drawParticles(Graphics *graphics);
    void getLights(QList<PointLight *> &lights);

protected:
    ParticleStreamSystem *m_particleSystem;
    PointLight *m_light;

    Camera *m_camera;
};

#endif // GAMEENTITY_H
