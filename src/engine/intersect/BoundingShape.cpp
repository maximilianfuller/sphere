#include "engine/intersect/BoundingShape.h"

BoundingShape::BoundingShape(glm::vec3 pos) :
    m_pos(pos)
{
}

BoundingShape::~BoundingShape()
{
}

glm::vec3 BoundingShape::getPosition()
{
    return m_pos;
}

void BoundingShape::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}
