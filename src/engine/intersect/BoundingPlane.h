#ifndef BOUNDINGPLANE_H
#define BOUNDINGPLANE_H

#include "engine/intersect/BoundingShape.h"

class BoundingCylinder;

class BoundingPlane : public BoundingShape
{
public:
    BoundingPlane(float level);
    ~BoundingPlane();

    bool intersect(BoundingShape *shape, glm::vec3 &mtv);
    bool intersect(BoundingPlane *plane, glm::vec3 &mtv);
    bool intersect(BoundingCylinder *cyl, glm::vec3 &mtv);
    bool intersect(BoundingBox *box, glm::vec3 &mtv);

    float getLevel();
    void setLevel(float level);

private:
    float m_level;
};

#endif // BOUNDINGPLANE_H
