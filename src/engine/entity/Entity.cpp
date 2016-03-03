#include "engine/entity/Entity.h"

#include "engine/world/World.h"
#include "engine/intersect/BoundingShape.h"
#include "engine/graphics/Controller.h"
#include "engine/shape/Shape.h"

Entity::Entity(World *world, glm::vec3 pos, glm::vec3 dims) :
    m_world(world),
    m_boundingShape(NULL),
    m_shape(NULL),
    m_pos(pos),
    m_dims(dims)
{
}

Entity::~Entity()
{
    delete m_shape;
    delete m_boundingShape;
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
    return;
}

void Entity::onDraw(Graphics::Controller *graphics)
{
    m_shape->draw(graphics);
}
