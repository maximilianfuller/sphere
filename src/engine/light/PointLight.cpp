#include "PointLight.h"

#include "engine/graphics/Graphics.h"

PointLight::PointLight(glm::vec3 pos, float shapeRadius,
                       glm::vec3 intensity, glm::vec3 att) :
    m_shapeRadius(shapeRadius),
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
    float minIntensity = 256.0 / 5.0;
    float maxIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));

    /* Calculated the radius in which the light is effective */
    m_lightRadius = (-m_att.y
                     + glm::sqrt(m_att.y * m_att.y - 4 * m_att.z
                                 * (m_att.x - minIntensity * maxIntensity)))
            / (2.0 * m_att.z);
}

glm::vec3 PointLight::getLightColor()
{
    return glm::mix(m_int, glm::vec3(1), 0.5);
}

float PointLight::getShapeRadius()
{
    return m_shapeRadius;
}

void PointLight::setShapeRadius(float shapeRadius)
{
    m_shapeRadius = shapeRadius;
}

float PointLight::getLightRadius()
{
    return m_lightRadius;
}

void PointLight::setLightRadius(float lightRadius)
{
    if(lightRadius != m_lightRadius)
    {
        float minIntensity = 256.0 / 5.0;
        float maxIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));
        float k = (minIntensity * maxIntensity) / (lightRadius * lightRadius);

        m_att = glm::vec3(0, 0, k);
        m_lightRadius = lightRadius;
    }
}

void PointLight::draw(Graphics *graphics)
{
    Light::draw(graphics);

    /* Send light uniforms */
    graphics->sendLightTypeUniform(POINT_LIGHT);
    graphics->sendAttenuationUniform(m_att);
    graphics->sendLightPositionUniform(m_pos);
    graphics->sendLightRadiusUniform(m_lightRadius);

    graphics->drawShape("fullscreenQuad");
}

void PointLight::drawGeometry(Graphics *graphics)
{
    Light::draw(graphics);

    /* Get geometry model matrix */
    glm::vec3 scale = glm::vec3(m_shapeRadius * 2, m_shapeRadius * 2,
                                m_shapeRadius * 2);
    glm::mat4x4 model = glm::translate(glm::mat4x4(), m_pos)
            * glm::scale(glm::mat4x4(), scale);

    /* Get updated color */
    glm::vec3 mixed = glm::mix(m_int, glm::vec3(1), 0.5);
    float power = glm::min(m_lightRadius / 100.f, 1.f);
    glm::vec4 color = glm::vec4(mixed, power);

    /* Send geometry uniforms */
    graphics->sendModelUniform(model);
    graphics->sendLightRadiusUniform(m_shapeRadius * 2);
    graphics->sendLightPositionUniform(m_pos);
    graphics->sendColorUniform(color);

    graphics->drawShape("sphere");
}
