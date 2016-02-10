#include "engine/shape/Shape.h"

#include "engine/graphics/Controller.h"

Shape::Shape(glm::mat4x4 model) :
    m_model(model)
{
}

Shape::~Shape()
{
}

glm::mat4x4 Shape::getModelMatrix()
{
    return m_model;
}

void Shape::setModelMatrix(glm::mat4x4 model)
{
    m_model = model;
}

void Shape::draw(Graphics::Controller *graphics)
{
    graphics->sendModelUniform(m_model, "default");
}
