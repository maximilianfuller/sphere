#include "engine/shape/Ellipsoid.h"

#include "engine/graphics/Controller.h"

Ellipsoid::Ellipsoid(glm::vec3 pos, glm::vec3 dims, glm::vec4 color) :
    Shape(pos, dims, color)
{
}

Ellipsoid::~Ellipsoid()
{
}

void Ellipsoid::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(0, "default");
    graphics->drawShape("sphere");
}
