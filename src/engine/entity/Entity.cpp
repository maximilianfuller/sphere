#include "engine/entity/Entity.h"

#include "engine/entity/BoundingShape.h"
#include "engine/graphics/Controller.h"
#include "engine/shape/Shape.h"

Entity::Entity() :
    m_shape(NULL),
    m_boundingShape(NULL)
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

bool Entity::hasIntersection(Entity *ent)
{
    return m_boundingShape->intersect(ent->getBoundingShape());
}

void Entity::draw(Graphics::Controller *graphics)
{
    m_shape->draw(graphics);
}
