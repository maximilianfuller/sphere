#include "engine/shape/Shape.h"

#include "engine/graphics/Controller.h"

Shape::Shape(glm::vec3 pos, glm::vec3 dims, glm::vec3 color) :
    m_model(glm::mat4x4()),
    m_color(color)
{
    setPosition(pos);
    setDimensions(dims);
}

Shape::Shape(glm::mat4x4 model, glm::vec3 color) :
    m_model(model),
    m_color(color)
{
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

// NOTE: setDimensions and setPosition should not be called outside
// of the engine code, and need to be called in a specific order.
glm::vec3 Shape::getPosition()
{
    return m_pos;
}

void Shape::setPosition(glm::vec3 pos)
{
    m_pos = pos;
    m_pos.y += 0.5f * m_dims.y;

    glm::mat4x4 model = glm::mat4x4();

    m_model = glm::translate(model, m_pos) * m_model;
}

glm::vec3 Shape::getDimensions()
{
    return m_dims;
}

void Shape::setDimensions(glm::vec3 dims)
{
    m_dims = dims;

    glm::mat4x4 model = glm::mat4x4();

    m_model = glm::scale(model, m_dims);
}

glm::vec3 Shape::getColor()
{
    return m_color;
}

void Shape::setColor(glm::vec3 color)
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

void Shape::draw(Graphics::Controller *graphics)
{
    graphics->sendModelUniform(m_model, "default");
    graphics->sendColorUniform(m_color, "default");
}
