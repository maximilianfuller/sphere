#ifndef PASSIVEENEMY_H
#define PASSIVEENEMY_H

#include "platformer/entity/Enemy.h"

class PassiveEnemy : public Enemy
{
public:
    PassiveEnemy(World *world,
                 float power, glm::vec3 color,
                 glm::vec3 pos = glm::vec3(0, 0, 0),
                 float speed = 1,
                 glm::vec3 vel = glm::vec3(0, 0, 0),
                 glm::vec3 acc = glm::vec3(0, G, 0),
                 glm::vec3 goal = glm::vec3(0, 0, 0),
                 float friction = MU_GROUND);
    virtual ~PassiveEnemy();

    void updateGoalVelocity();
};

#endif // PASSIVEENEMY_H
