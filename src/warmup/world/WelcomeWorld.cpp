#include "engine/camera/Camera.h"

#include "warmup/world/WelcomeWorld.h"
#include "warmup/entity/WelcomeMessage.h"

WelcomeWorld::WelcomeWorld()
{
    addEntity(new WelcomeMessage());
}

WelcomeWorld::~WelcomeWorld()
{
}
