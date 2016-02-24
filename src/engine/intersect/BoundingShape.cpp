#include "engine/intersect/BoundingShape.h"

BoundingShape::BoundingShape(glm::vec3 pos, glm::vec3 dims) :
    m_pos(pos),
    m_dims(dims)
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

glm::vec3 BoundingShape::getDimensions()
{
    return m_dims;
}

void BoundingShape::setDimensions(glm::vec3 dims)
{
    m_dims = dims;
}
