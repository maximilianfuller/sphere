#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "engine/intersect/BoundingShape.h"


class BoundingBox : public BoundingShape
{
public:
    BoundingBox();
    ~BoundingBox();

    bool intersect(BoundingShape *shape, glm::vec3 &mtv);
    bool intersect(BoundingPlane *plane, glm::vec3 &mtv);
    bool intersect(BoundingCylinder *cyl, glm::vec3 &mtv);
    bool intersect(BoundingBox *box, glm::vec3 &mtv);

private:
    float m_width, m_height, m_depth;
};

#endif // BOUNDINGBOX_H
