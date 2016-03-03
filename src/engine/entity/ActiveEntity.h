#ifndef ACTIVEENTITY_H
#define ACTIVEENTITY_H

#include "engine/entity/Entity.h"

#include "engine/world/WorldConstants.h"

class World;
class BackgroundEntity;

class ActiveEntity : public virtual Entity
{
public:
    ActiveEntity(World *world, float speed = 1,
                 glm::vec3 vel = glm::vec3(0, 0, 0),
                 glm::vec3 acc = glm::vec3(0, G, 0),
                 glm::vec3 goal = glm::vec3(0, 0, 0),
                 float friction = MU_GROUND);
    ~ActiveEntity();

    float getSpeed();
    void setSpeed(float speed);

    glm::vec3 getVelocity();
    void setVelocity(glm::vec3 vel);

    glm::vec3 getAcceleration();
    void setAcceleration(glm::vec3 acc);

    glm::vec3 getGoalVelocity();
    void setGoalVelocity(glm::vec3 goal);

    float getFriction();
    void setFriction(float friction);

    bool getGrounded();
    void setGrounded(bool grounded);

    virtual bool intersect(ActiveEntity *ent);
    virtual bool intersect(BackgroundEntity *ent);

    virtual void updateFriction() = 0;
    virtual void updateGoalVelocity() = 0;
    virtual void updateAcceleration() = 0;
    virtual void updateVelocity(float seconds);
    virtual void updatePosition(float seconds);

    virtual void onTick(float seconds);

protected:
    glm::vec3 m_vel;
    glm::vec3 m_acc;
    glm::vec3 m_goal;

    float m_speed;
    float m_friction;

    bool m_grounded;
};

#endif // ACTIVEENTITY_H
