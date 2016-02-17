#ifndef BOUNDINGCYLINDER_H
#define BOUNDINGCYLINDER_H

#include "engine/intersect/BoundingShape.h"

class BoundingPlane;

class BoundingCylinder : public BoundingShape
{
public:
    BoundingCylinder(glm::vec3 pos, float radius, float height);
    ~BoundingCylinder();

    float getRadius();
    void setRadius(float radius);

    float getHeight();
    void setHeight(float height);

    bool intersect(BoundingShape *shape, glm::vec3 &mtv);
    bool intersect(BoundingPlane *plane, glm::vec3 &mtv);
    bool intersect(BoundingCylinder *cyl, glm::vec3 &mtv);
    bool intersect(BoundingBox *box, glm::vec3 &mtv);

private:
    float m_radius;
    float m_height;
};

#endif // BOUNDINGCYLINDER_H
