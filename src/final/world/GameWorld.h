#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/world/World.h"

class Graphics;
class Camera;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera);
    ~GameWorld();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Game loop */
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
};

#endif // GAMEWORLD_H
