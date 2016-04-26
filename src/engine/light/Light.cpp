#include "Light.h"

#include "engine/graphics/Graphics.h"

Light::Light(glm::vec3 intensity, int lightId) :
    m_int(intensity),
    m_id(lightId)
{
}
glm::vec3 Light::getIntensity()
{
    return m_int;
}

void Light::setIntensity(glm::vec3 intensity)
{
    m_int = intensity;
}

void Light::draw(Graphics *graphics)
{
    graphics->sendIntensityUniform(m_int);
    graphics->setStencilId(m_id);
}

void Light::drawGeometry(Graphics *graphics)
{
    graphics->sendIntensityUniform(m_int);
    graphics->setStencilId(m_id);
}
