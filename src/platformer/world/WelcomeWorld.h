#ifndef WELCOMEWORLD_H
#define WELCOMEWORLD_H

#include "engine/world/World.h"

class Graphics;
class Camera;
class FullscreenQuad;

class WelcomeWorld : public World
{
public:
    WelcomeWorld(Camera *camera);
    ~WelcomeWorld();

    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);

private:
    FullscreenQuad *m_message;
};

#endif // WELCOMESCENE_H
