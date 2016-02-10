#include "BoundingPlane.h"

BoundingPlane::BoundingPlane(float level) :
    m_level(level)
{
}

BoundingPlane::~BoundingPlane()
{
}

ShapeType BoundingPlane::getShapeType() const
{
    return PlaneType;
}

float BoundingPlane::getLevel()
{
    return m_level;
}

void BoundingPlane::setLevel(float level)
{
    m_level = level;
}
