#include "engine/shape/Cylinder.h"

#include "engine/graphics/Controller.h"

Cylinder::Cylinder(glm::vec3 color, glm::mat4x4 model) :
    Shape(model, color)
{
}

Cylinder::~Cylinder()
{
}

void Cylinder::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(0, "default");
    graphics->drawShape("cylinder");
}
