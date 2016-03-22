#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/world/World.h"

namespace Graphics
{
class Controller;
}
class Camera;
class Player;
class OBJ;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera, Graphics::Controller *graphics,
              QString levelFile, QString levelKey);
    ~GameWorld();

    Player *getPlayer();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Game loop */
    void onTick(float seconds);
    void onDraw(Graphics::Controller *graphics);

private:
    Player *m_player;

    OBJ *m_level;
    QString m_levelKey;
};

#endif // GAMEWORLD_H
