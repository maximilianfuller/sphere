#ifndef WELCOMEWORLD_H
#define WELCOMEWORLD_H

#include "engine/world/World.h"

namespace Graphics
{
class Controller;
}
class Camera;
class FullscreenQuad;

class WelcomeWorld : public World
{
public:
    WelcomeWorld(Camera *camera);
    ~WelcomeWorld();

    void onTick(float seconds);
    void onDraw(Graphics::Controller *graphics);

private:
    FullscreenQuad *m_message;
};

#endif // WELCOMESCENE_H
