#include "warmup/entity/WelcomeMessage.h"

#include "engine/shape/FullscreenQuad.h"

WelcomeMessage::WelcomeMessage()
{
    m_shape = new FullscreenQuad("welcome");
}

WelcomeMessage::~WelcomeMessage()
{
}
