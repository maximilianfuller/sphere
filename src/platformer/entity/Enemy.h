#ifndef ENEMY_H
#define ENEMY_H

#include "platformer/entity/GameEntity.h"

class Graphics;
class World;

class PointLight;
class ParticleStreamSystem;

class Enemy : public GameEntity
{
public:
    Enemy(World *world,
          float power, glm::vec3 color,
          glm::vec3 pos = glm::vec3(0, 0, 0),
          glm::vec3 dims = glm::vec3(1, 1, 1),
          float speed = 1,
          glm::vec3 vel = glm::vec3(0, 0, 0),
          glm::vec3 acc = glm::vec3(0, G, 0),
          glm::vec3 goal = glm::vec3(0, 0, 0),
          float friction = MU_GROUND);
    virtual ~Enemy();

    GameEntity *getTarget();
    void setTarget(GameEntity *target);

    GameEntity *getFollower();
    void setFollower(GameEntity *follower);

    /* Entity interactions */
    void tryConnect(GameEntity *entity);
    void onConnected(GameEntity *entity);

    /* Game loop */
    void updateGoalVelocity();
    void onTick(float seconds);

protected:
    GameEntity *m_target;
    GameEntity *m_follower;
};

#endif // ENEMY_H
