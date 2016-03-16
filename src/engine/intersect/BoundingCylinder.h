#ifndef BOUNDINGCYLINDER_H
#define BOUNDINGCYLINDER_H

#include "engine/intersect/BoundingShape.h"

class BoundingPlane;

class BoundingCylinder : public BoundingShape
{
public:
    BoundingCylinder(glm::vec3 pos, glm::vec3 dims);
    ~BoundingCylinder();
};

#endif // BOUNDINGCYLINDER_H
