#ifndef MINECRAFTWELCOMEWORLD_H
#define MINECRAFTWELCOMEWORLD_H

#include "engine/world/World.h"

class Camera;

class MinecraftWelcomeWorld : public World
{
public:
    MinecraftWelcomeWorld(Camera *camera);
    ~MinecraftWelcomeWorld();
};

#endif // MINECRAFTWELCOMEWORLD_H
