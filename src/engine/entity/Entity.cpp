#include "engine/entity/Entity.h"

#include "engine/world/World.h"
#include "engine/intersect/BoundingShape.h"
#include "engine/graphics/Controller.h"
#include "engine/shape/Shape.h"

Entity::Entity(World *world, glm::vec3 pos) :
    m_world(world),
    m_boundingShape(NULL),
    m_shape(NULL),
    m_pos(pos)
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
