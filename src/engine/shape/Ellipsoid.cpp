#include "engine/shape/Ellipsoid.h"

#include "engine/graphics/Graphics.h"

Ellipsoid::Ellipsoid(glm::vec3 pos, glm::vec3 dims, glm::vec4 color) :
    Shape(pos, dims, color)
{
    setPosition(pos);
}

Ellipsoid::~Ellipsoid()
{
}

void Ellipsoid::draw(Graphics *graphics)
{
    Shape::draw(graphics);

    graphics->sendUseTextureUniform(0);
    graphics->drawShape("sphere");
}
