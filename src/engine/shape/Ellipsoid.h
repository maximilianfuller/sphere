#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "engine/shape/Shape.h"

class Graphics;

class Ellipsoid : public Shape
{
public:
    Ellipsoid(glm::vec3 pos = glm::vec3(0, 0, 0),
             glm::vec3 dims = glm::vec3(1, 1, 1),
             glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1.0));
    ~Ellipsoid();

    void draw(Graphics *graphics);
};

#endif // ELLIPSOID_H
