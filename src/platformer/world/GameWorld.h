#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/world/World.h"
#include "engine/intersect/Ray.h"

class Graphics;
class Camera;
class Player;
class GameEntity;
class PlanetManager;
class ParticleTube;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera, Graphics *graphics);
    ~GameWorld();

    Player *getPlayer();

    void stop();
    void start();

    bool getStopped();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    /* Game loop */
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
    void drawLightGeometry(Graphics *graphics);

    const float LOOK_ANGLE_EPS = 0.001;

    /*allow access to terrain data*/
    float getTerrainHeight(glm::vec3 loc); //returns terrain height at given location (length of ray from orign to terran defined by loc)

private:
    Player *m_player;
    PlanetManager *m_planet;
    QList<Triangle *> m_triangles;

    ParticleTube *m_northSystem;
    ParticleTube *m_southSystem;

    bool m_stopped;
    bool m_dead;
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
