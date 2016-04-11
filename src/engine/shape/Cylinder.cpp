#include "engine/shape/Cylinder.h"

#include "engine/graphics/Graphics.h"

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 dims, glm::vec4 color) :
    Shape(pos, dims, color)
{
}

Cylinder::~Cylinder()
{
}

void Cylinder::draw(Graphics *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(0);
    graphics->drawShape("cylinder");
}
