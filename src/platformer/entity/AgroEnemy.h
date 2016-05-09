#ifndef AGROENEMY_H
#define AGROENEMY_H

#include "platformer/entity/Enemy.h"

class AgroEnemy : public Enemy
{
public:
    AgroEnemy(World *world,
              float power, glm::vec3 color,
              glm::vec3 pos = glm::vec3(0, 0, 0),
              glm::vec3 dims = glm::vec3(1, 1, 1),
              float speed = 1,
              glm::vec3 vel = glm::vec3(0, 0, 0),
              glm::vec3 acc = glm::vec3(0, G, 0),
              glm::vec3 goal = glm::vec3(0, 0, 0),
              float friction = MU_GROUND);
    virtual ~AgroEnemy();

    void updateGoalVelocity();
};

#endif // AGROENEMY_H
