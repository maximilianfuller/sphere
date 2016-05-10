#ifndef VULTUREENEMY_H
#define VULTUREENEMY_H

#include "platformer/entity/Enemy.h"

const int VULTURE_VISION = 3;

class VultureEnemy : public Enemy
{
public:
    VultureEnemy(World *world,
                 float power, glm::vec3 color,
                 glm::vec3 pos = glm::vec3(0, 0, 0),
                 float speed = 1,
                 glm::vec3 vel = glm::vec3(0, 0, 0),
                 glm::vec3 acc = glm::vec3(0, G, 0),
                 glm::vec3 goal = glm::vec3(0, 0, 0),
                 float friction = MU_GROUND);
    virtual ~VultureEnemy();

    void updateGoalVelocity();
};

#endif // VULTUREENEMY_H
