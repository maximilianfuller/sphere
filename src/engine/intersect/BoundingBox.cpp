#include "engine/intersect/BoundingBox.h"

#include "engine/intersect/BoundingCylinder.h"
#include "engine/intersect/BoundingPlane.h"

BoundingBox::BoundingBox()
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
