#include "engine/intersect/BoundingBox.h"

#include "engine/intersect/BoundingCylinder.h"
#include "engine/intersect/BoundingPlane.h"

BoundingBox::BoundingBox(float width, float height, float depth) :
    m_width(width),
    m_height(height),
    m_depth(depth)
{
}

BoundingBox::~BoundingBox()
{
}

bool BoundingBox::intersect(BoundingShape *shape, glm::vec3 &mtv)
{
    return shape->intersect(this, mtv);
}

bool BoundingBox::intersect(BoundingPlane *plane, glm::vec3 &mtv)
{
    return false;
}

bool BoundingBox::intersect(BoundingCylinder *cyl, glm::vec3 &mtv)
{
    return false;
}

bool BoundingBox::intersect(BoundingBox *box, glm::vec3 &mtv)
{
    return false;
}
