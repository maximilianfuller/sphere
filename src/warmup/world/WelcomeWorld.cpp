#include "warmup/world/WelcomeWorld.h"

#include "engine/camera/Camera.h"

#include "warmup/entity/WelcomeMessage.h"

WelcomeWorld::WelcomeWorld(Camera *camera) :
    World(camera)
{
    addBackgroundEntity(new WelcomeMessage(this));
}

WelcomeWorld::~WelcomeWorld()
{
}
