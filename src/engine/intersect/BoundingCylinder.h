#ifndef BOUNDINGCYLINDER_H
#define BOUNDINGCYLINDER_H

#include "engine/intersect/BoundingShape.h"

class BoundingPlane;

class BoundingCylinder : public BoundingShape
{
public:
    BoundingCylinder(glm::vec3 pos, glm::vec3 dims);
    ~BoundingCylinder();

    bool intersect(BoundingShape *shape, glm::vec3 &mtv);
    bool intersect(BoundingPlane *plane, glm::vec3 &mtv);
    bool intersect(BoundingCylinder *cyl, glm::vec3 &mtv);
    bool intersect(BoundingBox *box, glm::vec3 &mtv);
};

#endif // BOUNDINGCYLINDER_H
