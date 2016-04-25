#include "platformer/world/WelcomeWorld.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/light/DirectionalLight.h"
#include "engine/shape/FullscreenQuad.h"

WelcomeWorld::WelcomeWorld(Camera *camera) :
    World(camera)
{
    m_message = new FullscreenQuad("welcome");

    addDirectionalLight(new DirectionalLight(glm::vec3(1, 1, 1),
                                             glm::vec3(1, 1, 1), 1));
}

WelcomeWorld::~WelcomeWorld()
{
}

void WelcomeWorld::onTick(float seconds)
{
    return;
}

void WelcomeWorld::drawGeometry(Graphics *graphics)
{
    graphics->sendEmptyMatrices();
    m_camera->setResolution(graphics);
    m_message->draw(graphics);
}

void WelcomeWorld::drawLights(Graphics *graphics)
{
    graphics->sendAmbientCoefficient(1.0);
    graphics->sendDiffuseCoefficient(0.0);
    graphics->sendSpecularCoefficient(0.0);

    World::drawLights(graphics);

    graphics->sendAmbientCoefficient(0.0);
    graphics->sendDiffuseCoefficient(1.0);
    graphics->sendSpecularCoefficient(0.8);
}
