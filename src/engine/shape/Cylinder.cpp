#include "engine/shape/Cylinder.h"

#include "engine/graphics/Controller.h"

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 dims, glm::vec3 color) :
    Shape(pos, dims, color)
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
