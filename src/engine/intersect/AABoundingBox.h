#ifndef AABOUNDINGBOX_H
#define AABOUNDINGBOX_H

#include "util/CommonIncludes.h"

class AABoundingBox
{
public:
    AABoundingBox(glm::vec3 pos = glm::vec3(0, 0, 0),
                glm::vec3 dims = glm::vec3(1, 1, 1));

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getDimensions();
    void setDimensions(glm::vec3 dims);

private:
    glm::vec3 m_pos;
    glm::vec3 m_dims;
};

#endif // AABOUNDINGBOX_H
