#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/world/World.h"
#include "engine/intersect/Ray.h"

class Graphics;
class Camera;
class Player;
class GameEntity;
class Planet;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera, Graphics *graphics);
    ~GameWorld();

    Player *getPlayer();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Game loop */
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
    void drawLightGeometry(Graphics *graphics);

private:
    Player *m_player;
    Planet *m_planet;

    QList<Triangle *> m_triangles;
};

class CompareDepth
{
public:
    bool operator()(std::pair<GameEntity *,float> n1,
                    std::pair<GameEntity *,float> n2)
    {
        return n1.second < n2.second;
    }
};

#endif // GAMEWORLD_H
