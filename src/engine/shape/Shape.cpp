#include "engine/shape/Shape.h"

#include "engine/graphics/Graphics.h"

Shape::Shape(glm::vec3 pos, glm::vec3 dims, glm::vec4 color) :
    m_model(glm::mat4x4()),
    m_color(color)
{
    setPosition(pos);
    setDimensions(dims);
}

Shape::~Shape()
{
}

void Shape::rotate(glm::mat4x4 model, glm::vec3 axis, float angle)
{
    glm::mat4x4 rotation = glm::mat4x4();

    m_model = glm::rotate(rotation, angle, axis) * model;
}

void Shape::translate(glm::mat4x4 model, glm::vec3 move)
{
    glm::mat4x4 translation = glm::mat4x4();

    m_model = glm::translate(translation, move) * model;
}

glm::vec3 Shape::getPosition()
{
    return m_pos;
}

void Shape::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 Shape::getDimensions()
{
    return m_dims;
}

void Shape::setDimensions(glm::vec3 dims)
{
    m_dims = dims;
}

glm::vec4 Shape::getColor()
{
    return m_color;
}

void Shape::setColor(glm::vec4 color)
{
    m_color = color;
}

glm::mat4x4 Shape::getModelMatrix()
{
    return m_model;
}

void Shape::setModelMatrix(glm::mat4x4 model)
{
    m_model = model;
}

void Shape::draw(Graphics *graphics)
{
    glm::mat4x4 model = glm::mat4x4();
    m_model = glm::translate(model, m_pos) * glm::scale(model, m_dims);

    graphics->sendModelUniform(m_model);
    graphics->sendColorUniform(m_color);
}
