#include "PointLight.h"

#include "engine/graphics/Graphics.h"

PointLight::PointLight(glm::vec3 pos,glm::vec3 intensity, glm::vec3 att) :
    Light(intensity)
{
    setPosition(pos);
    setAttenuation(att);
}

glm::vec3 PointLight::getPosition()
{
    return m_pos;
}

void PointLight::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 PointLight::getAttenuation()
{
    return m_att;
}

void PointLight::setAttenuation(glm::vec3 att)
{
    m_att = att;

    /* Get minimum tolerated intensity and max light intensity */
    float maxIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));

    /* Calculated the radius in which the light is effective */
    m_radius = (-m_att.y
                + glm::sqrt(m_att.y * m_att.y - 4 * m_att.z
                            * (m_att.x - (1 / MIN_INTENSITY) * maxIntensity)))
            / (2.0 * m_att.z);
}

glm::vec3 PointLight::getLightColor()
{
    return glm::mix(m_int, glm::vec3(1), 0.5);
}

float PointLight::getRadius()
{
    return m_radius;
}

void PointLight::setRadius(float radius)
{
    radius = radius;

    if(radius != m_radius)
    {
        float maxIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));
        float k = ((1 / MIN_INTENSITY) * maxIntensity) / (radius * radius);

        m_att = glm::vec3(0, 0, k);
        m_radius = radius;
    }
}

void PointLight::draw(Graphics *graphics)
{
    Light::draw(graphics);

    /* Send light uniforms */
    glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(m_radius, m_radius, m_radius) * 2.f);
    glm::mat4 translate = glm::translate(glm::mat4(), m_pos);
    graphics->sendModelUniform(translate * scale);

    graphics->sendLightTypeUniform(POINT_LIGHT);
    graphics->sendAttenuationUniform(m_att);
    graphics->sendLightPositionUniform(m_pos);
    graphics->sendLightRadiusUniform(m_radius);

    graphics->drawShape("sphere");
}
