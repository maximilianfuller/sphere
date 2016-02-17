#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H

#include "util/CommonIncludes.h"

class BoundingPlane;
class BoundingCylinder;
class BoundingBox;

class BoundingShape
{
public:
    BoundingShape(glm::vec3 pos = glm::vec3(0, 0, 0));
    virtual ~BoundingShape();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    virtual bool intersect(BoundingShape *shape, glm::vec3 &mtv) = 0;
    virtual bool intersect(BoundingPlane *plane, glm::vec3 &mtv) = 0;
    virtual bool intersect(BoundingCylinder *cyl, glm::vec3 &mtv) = 0;
    virtual bool intersect(BoundingBox *box, glm::vec3 &mtv) = 0;

protected:
    glm::vec3 m_pos;
};

#endif // BOUNDINGSHAPE_H
