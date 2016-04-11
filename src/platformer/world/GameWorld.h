#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/world/World.h"

class Graphics;
class Camera;
class Player;
class Ellipsoid;
class OBJ;
class Ray;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera, Graphics *graphics,
              QString levelFile, QString levelKey);
    ~GameWorld();

    Player *getPlayer();

    Ray getRay(int mouseX, int mouseY);
    void setTarget();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Game loop */
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);

private:
    Player *m_player;
    Ellipsoid *m_target;

    OBJ *m_level;
    QString m_levelKey;
};

#endif // GAMEWORLD_H
