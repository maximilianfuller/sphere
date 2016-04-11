#include "engine/entity/Entity.h"

#include "engine/world/World.h"
#include "engine/intersect/BoundingShape.h"
#include "engine/graphics/Graphics.h"
#include "engine/shape/Shape.h"

Entity::Entity(World *world, glm::vec3 pos, glm::vec3 dims,
               float speed, glm::vec3 vel, glm::vec3 acc,
               glm::vec3 goal, float friction) :
    m_world(world),
    m_boundingShape(NULL),
    m_shape(NULL),
    m_pos(pos),
    m_dims(dims),
    m_speed(speed),
    m_vel(vel),
    m_acc(acc),
    m_goal(goal),
    m_friction(friction),
    m_grounded(true)
{
}

Entity::~Entity()
{
    delete m_shape;
    delete m_boundingShape;
}

Shape *Entity::getShape() const
{
    return m_shape;
}

BoundingShape *Entity::getBoundingShape() const
{
    return m_boundingShape;
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

void Entity::updateFriction()
{
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
    m_pos.x += getSpeed() * getVelocity().x * seconds;
    m_pos.y += getVelocity().y * seconds;
    m_pos.z += getSpeed() * getVelocity().z * seconds;
}

void Entity::updateShape()
{
    m_shape->setDimensions(m_dims);
    m_shape->setPosition(m_pos);
}

void Entity::updateBoundingShape()
{
    if(m_boundingShape)
    {
        m_boundingShape->setDimensions(m_dims);
        m_boundingShape->setPosition(m_pos);
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

    /* Movement updates */
    updateFriction();
    updateGoalVelocity();
    updateAcceleration();
    updateVelocity(seconds);

    m_acc = glm::vec3(0, G, 0);

    updateShape();
    updateBoundingShape();
}

void Entity::onDraw(Graphics *graphics)
{
    m_shape->draw(graphics);
}
