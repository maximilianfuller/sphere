#include "engine/entity/ActiveEntity.h"

#include "engine/world/World.h"
#include "engine/intersect/BoundingShape.h"
#include "engine/entity/BackgroundEntity.h"

ActiveEntity::ActiveEntity(World *world, float speed, glm::vec3 vel, glm::vec3 acc,
                           glm::vec3 goal, float friction) :
    m_speed(speed),
    m_vel(vel),
    m_acc(acc),
    m_goal(goal),
    m_friction(friction),
    m_grounded(true),
    Entity(world)
{
}

ActiveEntity::~ActiveEntity()
{

}

float ActiveEntity::getSpeed()
{
    return m_speed;
}

void ActiveEntity::setSpeed(float speed)
{
    m_speed = speed;
}

glm::vec3 ActiveEntity::getVelocity()
{
    return m_vel;
}

void ActiveEntity::setVelocity(glm::vec3 vel)
{
    m_vel = vel;
}

glm::vec3 ActiveEntity::getAcceleration()
{
    return m_acc;
}

void ActiveEntity::setAcceleration(glm::vec3 acc)
{
    m_acc = acc;
}

glm::vec3 ActiveEntity::getGoalVelocity()
{
    return m_goal;
}

void ActiveEntity::setGoalVelocity(glm::vec3 goal)
{
    m_goal = goal;
}

float ActiveEntity::getFriction()
{
    return m_friction;
}

void ActiveEntity::setFriction(float friction)
{
    m_friction = friction;
}

bool ActiveEntity::getGrounded()
{
    return m_grounded;
}

void ActiveEntity::setGrounded(bool grounded)
{
    m_grounded = grounded;
}

void ActiveEntity::updateVelocity(float seconds)
{
    m_vel += m_acc * seconds;
}

void ActiveEntity::updatePosition(float seconds)
{
    m_pos.x += m_speed * m_vel.x * seconds;
    m_pos.y += m_vel.y * seconds;
    m_pos.z += m_speed * m_vel.z * seconds;
}

void ActiveEntity::onTick(float seconds)
{
    seconds = glm::min(1.f / 30.f, seconds);

    /* Movement updates */
    updatePosition(seconds);
    updateFriction();
    updateGoalVelocity();
    updateAcceleration();
    updateVelocity(seconds);

    m_acc = glm::vec3(0, G, 0);

    updateShape();
    updateBoundingShape();
}
