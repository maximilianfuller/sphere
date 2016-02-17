#include "engine/shape/Shape.h"

#include "engine/graphics/Controller.h"

Shape::Shape(glm::mat4x4 model, glm::vec3 color) :
    m_model(model),
    m_color(color)
{
}

Shape::~Shape()
{
}

void Shape::rotateAbsolute(glm::vec3 axis, float angle)
{
    glm::mat4x4 model = glm::mat4x4();

    m_model = glm::rotate(model, angle, axis);
}

void Shape::translateAbsolute(glm::vec3 move)
{
    glm::mat4x4 model = glm::mat4x4();

    m_model = glm::translate(model, move);
}

void Shape::rotateRelative(glm::vec3 axis, float angle)
{
    m_model = glm::rotate(m_model, angle, axis);
}

void Shape::translateRelative(glm::vec3 move)
{
    m_model = glm::translate(m_model, move);
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
    graphics->sendColorUniform(m_color, "default");
}
