#include "engine/light/Light.h"

Light::Light()
{

}

Light::~Light()
{

}

glm::vec3 Light::getPosition()
{
    return m_position;
}

void Light::setPosition(glm::vec3 &pos)
{
    m_position = pos;
}

glm::vec3 Light::getColor()
{
    return m_color;
}

void Light::setColor(glm::vec3 &color)
{
    m_color = color;
}
