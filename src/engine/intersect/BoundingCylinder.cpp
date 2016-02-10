#include "BoundingCylinder.h"

BoundingCylinder::BoundingCylinder(glm::vec3 pos, float radius, float height) :
    m_pos(pos),
    m_radius(radius),
    m_height(height)
{
}

BoundingCylinder::~BoundingCylinder()
{
}

ShapeType BoundingCylinder::getShapeType() const
{
    return CylinderType;
}

glm::vec3 BoundingCylinder::getPosition()
{
    return m_pos;
}

void BoundingCylinder::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}

float BoundingCylinder::getRadius()
{
    return m_radius;
}

void BoundingCylinder::setRadius(float radius)
{
    m_radius = radius;
}

float BoundingCylinder::getHeight()
{
    return m_height;
}

void BoundingCylinder::setHeight(float height)
{
    m_height = height;
}
