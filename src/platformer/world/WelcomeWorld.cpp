#include "platformer/world/WelcomeWorld.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/shape/FullscreenQuad.h"

WelcomeWorld::WelcomeWorld(Camera *camera) :
    World(camera)
{
    m_message = new FullscreenQuad("welcome");
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
    m_message->draw(graphics);
}
