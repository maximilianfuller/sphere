#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H

#include "util/CommonIncludes.h"

class BoundingCylinder;

class BoundingShape
{
public:
    BoundingShape(glm::vec3 pos = glm::vec3(0, 0, 0),
                  glm::vec3 dims = glm::vec3(0, 0, 0));
    virtual ~BoundingShape();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getDimensions();
    void setDimensions(glm::vec3 dims);

protected:
    glm::vec3 m_pos;
    glm::vec3 m_dims;
};

#endif // BOUNDINGSHAPE_H
