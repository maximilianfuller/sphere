#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "util/CommonIncludes.h"

class Triangle
{
public:
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    Triangle scale(glm::vec3 basis);

    bool visited;
    glm::vec3 vertices[3];
    glm::vec3 normal;
};

#endif // TRIANGLE_H
