#include "warmup/entity/WelcomeMessage.h"

#include "engine/world/World.h"
#include "engine/shape/FullscreenQuad.h"

WelcomeMessage::WelcomeMessage(World *world) :
    Entity(world),
    BackgroundEntity(world)
{
    m_shape = new FullscreenQuad("welcome");
}

WelcomeMessage::~WelcomeMessage()
{
}
