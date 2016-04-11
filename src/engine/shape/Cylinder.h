#ifndef CYLINDER_H
#define CYLINDER_H

#include "engine/shape/Shape.h"

class Graphics;

class Cylinder : public Shape
{
public:
    Cylinder(glm::vec3 pos = glm::vec3(0, 0, 0),
             glm::vec3 dims = glm::vec3(1, 1, 1),
             glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1.0));
    ~Cylinder();

    void draw(Graphics *graphics);
};

#endif // CYLINDER_H
