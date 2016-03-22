#include "platformer/world/WelcomeWorld.h"

#include "engine/graphics/Controller.h"
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

void WelcomeWorld::onDraw(Graphics::Controller *graphics)
{
    m_message->draw(graphics);
}
