#ifndef WELCOMESCENE_H
#define WELCOMESCENE_H

#include "engine/world/World.h"

class Camera;

class WelcomeWorld : public World
{
public:
    WelcomeWorld(Camera *camera);
    ~WelcomeWorld();
};

#endif // WELCOMESCENE_H
