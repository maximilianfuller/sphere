#include "DirectionalLight.h"

#include "engine/graphics/Graphics.h"

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 intensity) :
    m_dir(dir),
    Light(intensity)
{
}

void DirectionalLight::draw(Graphics *graphics)
{
    Light::draw(graphics);

    graphics->sendLightTypeUniform(DIRECTIONAL_LIGHT);
    graphics->sendLightDirectionUniform(m_dir);
    graphics->drawShape("fullscreenQuad");
}
