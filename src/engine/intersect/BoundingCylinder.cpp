#include "engine/intersect/BoundingCylinder.h"

BoundingCylinder::BoundingCylinder(glm::vec3 pos, glm::vec3 dims) :
    BoundingShape(pos, dims)
{
}

BoundingCylinder::~BoundingCylinder()
{
}
