#include "minecraft/manager/MinecraftWelcomeWorld.h"

#include "engine/camera/Camera.h"

#include "warmup/entity/WelcomeMessage.h"

MinecraftWelcomeWorld::MinecraftWelcomeWorld(Camera *camera) :
    World(camera)
{
    addBackgroundEntity(new WelcomeMessage(this));
}

MinecraftWelcomeWorld::~MinecraftWelcomeWorld()
{
}
