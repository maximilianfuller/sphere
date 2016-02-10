#include "warmup/entity/WelcomeMessage.h"

#include "engine/shape/FullscreenQuad.h"

WelcomeMessage::WelcomeMessage()
{
    m_shape = new FullscreenQuad("welcome");
}

WelcomeMessage::~WelcomeMessage()
{
}

unsigned int WelcomeMessage::getEntityType()
{
    return 1;
}

bool WelcomeMessage::hasIntersection(Entity *ent)
{
    return false;
}

void WelcomeMessage::intersect(unsigned int e)
{
}

void WelcomeMessage::tick(float seconds)
{
}
