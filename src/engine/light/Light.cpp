#include "Light.h"

#include "engine/graphics/Graphics.h"

Light::Light(glm::vec3 intensity) :
    m_int(intensity)
{
    m_id = ++numLights;
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
    graphics->setStencilId(m_id);
    graphics->sendIntensityUniform(m_int);
}
