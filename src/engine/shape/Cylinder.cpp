#include "engine/shape/Cylinder.h"

#include "engine/graphics/Controller.h"

Cylinder::Cylinder(glm::mat4x4 model) :
    Shape(model)
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
