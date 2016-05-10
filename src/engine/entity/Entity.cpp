#include "engine/entity/Entity.h"

#include "engine/world/World.h"
#include "engine/graphics/Graphics.h"
#include "engine/shape/Shape.h"

Entity::Entity(World *world, glm::vec3 pos, glm::vec3 dims,
               float speed, glm::vec3 vel, glm::vec3 acc,
               glm::vec3 goal, float friction) :
    m_world(world),
    m_shape(NULL),
    m_pos(pos),
    m_dims(dims),
    m_speed(speed),
    m_vel(vel),
    m_acc(acc),
    m_goal(goal),
    m_friction(friction),
    m_grounded(true),
    m_moved(false)
{
}

Entity::~Entity()
{
    delete m_shape;
}

Shape *Entity::getShape() const
{
    return m_shape;
}

glm::vec3 Entity::getPosition()
{
    return m_pos;
}

void Entity::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 Entity::getDimensions()
{
    return m_dims;
}

void Entity::setDimensions(glm::vec3 dims)
{
    m_dims = dims;
}

float Entity::getSpeed()
{
    return m_speed;
}

void Entity::setSpeed(float speed)
{
    m_speed = speed;
}

glm::vec3 Entity::getVelocity()
{
    return m_vel;
}

void Entity::setVelocity(glm::vec3 vel)
{
    m_vel = vel;
}

glm::vec3 Entity::getAcceleration()
{
    return m_acc;
}

void Entity::setAcceleration(glm::vec3 acc)
{
    m_acc = acc;
}

glm::vec3 Entity::getGoalVelocity()
{
    return m_goal;
}

void Entity::setGoalVelocity(glm::vec3 goal)
{
    m_goal = goal;
}

float Entity::getFriction()
{
    return m_friction;
}

void Entity::setFriction(float friction)
{
    m_friction = friction;
}

bool Entity::getGrounded()
{
    return m_grounded;
}

void Entity::setGrounded(bool grounded)
{
    m_grounded = grounded;
}

bool Entity::getMoved()
{
    return m_moved;
}

void Entity::setMoved(bool moved)
{
    m_moved = moved;
}

void Entity::updateFriction()
{
    m_friction = m_grounded ? MU_GROUND : MU_AIR;
}

void Entity::updateGoalVelocity()
{
}

void Entity::updateAcceleration()
{
}

void Entity::updateVelocity(float seconds)
{
    m_vel += getAcceleration() * seconds;
}

void Entity::updatePosition(float seconds)
{
    if(!m_moved)
    {
        m_pos += getSpeed() * getVelocity() * seconds;
    }

    m_moved = false;
}

void Entity::updateShape()
{
    if(m_shape)
    {
        m_shape->setDimensions(m_dims);
        m_shape->setPosition(m_pos);
    }
}

bool Entity::intersect(Entity *ent)
{
    return false;
}

void Entity::onIntersect(Entity *ent, glm::vec3 mtv)
{
    return;
}

void Entity::onTick(float seconds)
{
    seconds = glm::min(1.f / 30.f, seconds);

    /* Update state */
    updateFriction();
    updateGoalVelocity();
    updateAcceleration();
    updateVelocity(seconds);
    updatePosition(seconds);
    updateShape();
}

void Entity::drawGeometry(Graphics *graphics)
{
    m_shape->draw(graphics);
}

void Entity::drawLights(Graphics *graphics)
{
}

void Entity::drawParticles(Graphics *graphics)
{
}

void Entity::drawLightGeometry(Graphics *graphics)
{
}
