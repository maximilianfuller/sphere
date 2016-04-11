#include "Light.h"

#include "engine/graphics/Graphics.h"

Light::Light(glm::vec3 pos, glm::vec3 att, glm::vec3 intensity) :
    m_model(glm::mat4x4()),
    m_int(intensity)
{
    setPosition(pos);
    setAttenuation(att);
}

glm::vec3 Light::getPosition()
{
    return m_pos;
}

void Light::setPosition(glm::vec3 pos)
{
    m_pos = pos;

    glm::mat4x4 model = glm::mat4x4();

    m_model = glm::translate(model, m_pos) * m_model;
}

glm::vec3 Light::getAttenuation()
{
    return m_att;
}

void Light::setAttenuation(glm::vec3 att)
{
    m_att = att;

    /* Get minimum tolerated intensity and max light intensity */
    float minIntensity = 256.0 / 5.0;
    float lightIntensity = glm::max(m_int.x, glm::max(m_int.y, m_int.z));

    /* Calculated the radius in which the light is effective */
    float radius = (-m_att.y
                    + glm::sqrt(m_att.y * m_att.y - 4 * m_att.z
                                * (m_att.x - minIntensity * lightIntensity)))
            / (2.0 * m_att.z);

    /* Scale the unit sphere to fit the radius of the light */
    glm::mat4x4 model = glm::mat4x4();
    glm::vec3 scale = glm::vec3(radius, radius, radius);

    m_model = glm::scale(model, scale);
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
    graphics->sendModelUniform(m_model);
    graphics->sendIntensityUniform(m_int);
    graphics->sendAttenuationUniform(m_att);
    graphics->sendLightPositionUniform(m_pos);

    graphics->drawShape("sphere");
}
