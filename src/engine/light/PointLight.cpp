#include "PointLight.h"

#include "engine/graphics/Graphics.h"

PointLight::PointLight(glm::vec3 pos, glm::vec3 att, glm::vec3 intensity,
             int lightId) :
    Light(intensity, lightId)
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
    float minIntensity = 256.0;
    float maxIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));

    /* Calculated the radius in which the light is effective */
    m_radius = (-m_att.y
                + glm::sqrt(m_att.y * m_att.y - 4 * m_att.z
                            * (m_att.x - minIntensity * maxIntensity)))
            / (2.0 * m_att.z);
}

glm::vec3 PointLight::getIntensity()
{
    return m_int;
}

void PointLight::setIntensity(glm::vec3 intensity)
{
    m_int = intensity;
}

float PointLight::getRadius()
{
    return m_radius;
}

void PointLight::setRadius(float radius)
{
    float lightRadius = radius / 0.05f;
    float minIntensity = 256.0;
    float maxIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));
    float k = (minIntensity * maxIntensity) / (lightRadius * lightRadius);

    m_att = glm::vec3(0, 0, k);
    m_radius = lightRadius;
}

void PointLight::draw(Graphics *graphics)
{
    Light::draw(graphics);

    /* Get model matrix */
    glm::vec3 scale = glm::vec3(m_radius, m_radius, m_radius);
    glm::mat4x4 model = glm::translate(glm::mat4x4(), m_pos)
            * glm::scale(glm::mat4x4(), scale);

    /* Send light uniforms */
    graphics->sendLightTypeUniform(POINT_LIGHT);
    graphics->sendModelUniform(model);
    graphics->sendAttenuationUniform(m_att);
    graphics->sendLightPositionUniform(m_pos);

    graphics->drawShape("sphere");
}

void PointLight::drawGeometry(Graphics *graphics)
{
    Light::draw(graphics);

    /* Get geometry model matrix */
    float geomRadius = 0.05f * m_radius;
    glm::vec3 scale = glm::vec3(geomRadius, geomRadius, geomRadius);
    glm::mat4x4 model = glm::translate(glm::mat4x4(), m_pos)
            * glm::scale(glm::mat4x4(), scale);

    /* Get updated color */
    glm::vec3 color = glm::mix(m_int, glm::vec3(1), 0.5);

    /* Send geometry uniforms */
    graphics->sendModelUniform(model);
    graphics->sendLightRadiusUniform(geomRadius);
    graphics->sendLightPositionUniform(m_pos);
    graphics->sendIntensityUniform(color);

    graphics->drawShape("sphere");
}
