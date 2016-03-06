#include "warmup/world/WelcomeWorld.h"
#include "warmup/entity/WelcomeMessage.h"

WelcomeWorld::WelcomeWorld()
{
    addBackgroundEntity(new WelcomeMessage(this));
}

WelcomeWorld::~WelcomeWorld()
{
}
