#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "engine/entity/Entity.h"

class Graphics;
class World;

class PointLight;

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

    /* Light and shape */
    float getRadius();
    void setRadius(float radius);

    float getLightRadius();
    glm::vec3 getLightPosition();
    glm::vec3 getLightColor();

    /* Power */
    float getPower();
    void setPower(float power);

    /* Delta */
    float getDelta();

    /* Stun */
    bool getStun();
    void setStun();

    /* Transfer rate */
    float getTransferRate(GameEntity *target);

    /* Entity interactions */
    bool hasTarget(GameEntity* target);
    void addTarget(GameEntity *target);
    int numTargets();
    void clearTargets();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
    void drawLights(Graphics *graphics);
    void drawParticles(Graphics *graphics);
    void drawLightGeometry(Graphics *graphics);

protected:
    PointLight *m_light;
    QList<GameEntity *> m_targets;

    float m_power;
    float m_time;
    float m_delta;

    bool m_warning;
    bool m_stun;

    int m_stunTimer;
};

#endif // GAMEENTITY_H
