#include "engine/intersect/AABoundingBox.h"

AABoundingBox::AABoundingBox(glm::vec3 pos, glm::vec3 dims) :
    m_pos(pos),
    m_dims(dims)
{
}

glm::vec3 AABoundingBox::getPosition()
{
    return m_pos;
}

void AABoundingBox::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 AABoundingBox::getDimensions()
{
    return m_dims;
}

void AABoundingBox::setDimensions(glm::vec3 dims)
{
    m_dims = dims;
}
