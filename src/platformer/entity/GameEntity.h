#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "engine/entity/Entity.h"

class Graphics;
class World;

class PointLight;
class ParticleStreamSystem;

class GameEntity : public Entity
{
public:
    GameEntity(World *world,
               float power, glm::vec3 color,
               glm::vec3 pos = glm::vec3(0, 0, 0),
               glm::vec3 dims = glm::vec3(1, 1, 1),
               float speed = 1,
               glm::vec3 vel = glm::vec3(0, 0, 0),
               glm::vec3 acc = glm::vec3(0, G, 0),
               glm::vec3 goal = glm::vec3(0, 0, 0),
               float friction = MU_GROUND);
    virtual ~GameEntity();

    /* Power */
    float getPower();
    void setPower(float power);

    /* Entity interactions */
    bool getConnected();
    void setConnected(bool connected);

    float getRadius();
    void setRadius(float radius);

    glm::vec3 getLightColor();

    virtual float getTransferRate();

    virtual void tryConnect(GameEntity *entity);
    virtual void onConnected(GameEntity *entity);
    virtual void transferPower(GameEntity *entity);

    /* Particles */
    void startStream();
    void stopStream();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
    void drawLights(Graphics *graphics);
    void drawParticles(Graphics *graphics);
    void drawLightGeometry(Graphics *graphics);

protected:
    ParticleStreamSystem *m_stream;
    PointLight *m_light;

    float m_power;
    bool m_connected;
};

#endif // GAMEENTITY_H
