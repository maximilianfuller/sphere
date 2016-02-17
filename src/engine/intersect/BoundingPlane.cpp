#include "engine/intersect/BoundingPlane.h"
#include "engine/intersect/BoundingCylinder.h"
#include "engine/intersect/BoundingBox.h"

BoundingPlane::BoundingPlane(float level) :
    m_level(level),
    BoundingShape()
{
}

BoundingPlane::~BoundingPlane()
{
}

bool BoundingPlane::intersect(BoundingShape *shape, glm::vec3 &mtv)
{
    return shape->intersect(this, mtv);
}

bool BoundingPlane::intersect(BoundingPlane *plane, glm::vec3 &mtv)
{
    return false;
}

bool BoundingPlane::intersect(BoundingCylinder *cyl, glm::vec3 &mtv)
{
    mtv = glm::vec3(0, cyl->getPosition().y - m_level, 0);
    return mtv.y < 0;
}

bool BoundingPlane::intersect(BoundingBox *box, glm::vec3 &mtv)
{
    return false;
}

float BoundingPlane::getLevel()
{
    return m_level;
}

void BoundingPlane::setLevel(float level)
{
    m_level = level;
}
