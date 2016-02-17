#include "engine/entity/ActiveEntity.h"

#include "engine/world/World.h"
#include "engine/intersect/BoundingShape.h"
#include "engine/entity/BackgroundEntity.h"

ActiveEntity::ActiveEntity(World *world, float speed, glm::vec3 pos,
                           glm::vec3 vel, glm::vec3 acc, glm::vec3 goal,
                           float friction) :
    m_vel(vel),
    m_acc(acc),
    m_goal(goal),
    m_speed(speed),
    m_friction(friction),
    m_grounded(true),
    Entity(world, pos)
{
}

ActiveEntity::~ActiveEntity()
{

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

bool ActiveEntity::intersect(ActiveEntity *ent)
{
    glm::vec3 mtv;

    if(m_boundingShape->intersect(ent->getBoundingShape(), mtv))
    {
        m_pos += 0.5f * mtv;
        ent->setPosition(ent->getPosition() - 0.5f * mtv);

        onIntersect(ent, mtv);
        ent->onIntersect(this, -mtv);

        return true;
    }

    return false;
}

bool ActiveEntity::intersect(BackgroundEntity *ent)
{
    glm::vec3 mtv;

    if(m_boundingShape->intersect(ent->getBoundingShape(), mtv))
    {
        m_pos += mtv;

        onIntersect(ent, mtv);
        ent->onIntersect(this, -mtv);

        return true;
    }

    return false;
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
    /* Movement updates */
    updateFriction();
    updateGoalVelocity();
    updateAcceleration();
    updateVelocity(seconds);
    updatePosition(seconds);

    /* Appearance update */
    updateShape();

    /* Bounding shape update */
    updateBoundingShape();
}
