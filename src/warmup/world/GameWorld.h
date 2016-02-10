#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "engine/graphics/Controller.h"
#include "engine/world/World.h"

class PerspectiveCamera;
class Player;

class GameWorld : public World
{
public:
    GameWorld(PerspectiveCamera *camera);
    ~GameWorld();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    PerspectiveCamera *m_camera;
    Player *m_player;
};

#endif // GAMESCENE_H
