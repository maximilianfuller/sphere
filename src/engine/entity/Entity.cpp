#include "engine/entity/Entity.h"

#include "engine/intersect/BoundingShape.h"
#include "engine/graphics/Controller.h"
#include "engine/shape/Shape.h"

Entity::Entity(glm::vec3 pos) :
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

void Entity::onIntersect(Entity *ent, glm::vec3 mtv)
{
    return;
}

void Entity::onDraw(Graphics::Controller *graphics)
{
    m_shape->draw(graphics);
}
