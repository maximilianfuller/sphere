#ifndef CYLINDER_H
#define CYLINDER_H

#include "engine/shape/Shape.h"

namespace Graphics
{
class Controller;
}

class Cylinder : public Shape
{
public:
    Cylinder(glm::mat4x4 model = glm::mat4x4());
    ~Cylinder();

    void draw(Graphics::Controller *graphics);
};

#endif // CYLINDER_H
