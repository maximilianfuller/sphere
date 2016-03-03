#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "engine/graphics/Controller.h"
#include "engine/world/World.h"

class Camera;
class Player;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera);
    ~GameWorld();

    Player *getPlayer();

    bool getGameOver();
    void setGameOver(bool val);

    void spawnZombie();
    void removeZombie();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Game loop */
    void onTick(float seconds);

private:
    Camera *m_camera;
    Player *m_player;

    int m_spawnCounter;

    int m_numLeft;
    int m_numSpawned;
    int m_numTotal;

    bool m_over;
};

#endif // GAMESCENE_H
