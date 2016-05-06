#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "engine/world/World.h"
#include "engine/intersect/Ray.h"

class Graphics;
class Camera;
class Player;
class Ellipsoid;
class OBJ;
class GameEntity;

const float RAY_LEN = 100.f;

class GameWorld : public World
{
public:
    GameWorld(Camera *camera, Graphics *graphics,
              QString levelFile, QString levelKey);
    ~GameWorld();

    Player *getPlayer();

    void setRay();
    void setTarget();
    void makePath();

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

    bool m_navFeatures;
    Ellipsoid *m_target;
    QList<Ellipsoid *> m_targetPath;
    Ray m_ray;

    OBJ *m_level;
    QString m_levelKey;
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
