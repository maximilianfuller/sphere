#ifndef PLAYER_H
#define PLAYER_H

#include "platformer/entity/GameEntity.h"

class Camera;

class Player : public GameEntity
{
public:
    Player(World *manager, Camera *camera);
    ~Player();

    /* User control */
    float getSpeed();

    bool getMoveFoward();
    void setMoveFoward(bool val);

    bool getMoveBackward();
    void setMoveBackward(bool val);

    bool getMoveLeft();
    void setMoveLeft(bool val);

    bool getMoveRight();
    void setMoveRight(bool val);

    bool getJump();
    void setJump(bool val);

    bool getZoomIn();
    void setZoomIn(bool val);

    bool getZoomOut();
    void setZoomOut(bool val);

    float getZoom();
    void setZoom(float zoom);

    /* Camera direction */
    glm::vec3 getDirection();

    /* Actions */
    void jump();
    void attack();

    /* Update methods on tick */
    void updateGoalVelocity();
    void updateCamera();

    /* Game loop */
    void onTick(float seconds);
    void drawGeometry(Graphics *graphics);
    void drawLightGeometry(Graphics *graphics);

private:
    /* Movement */
    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveLeft;
    bool m_moveRight;
    bool m_jump;
    bool m_zoomIn;
    bool m_zoomOut;

    float m_zoom;

    /* Attack */
    int m_attackTimer;

    /* Camera */
    Camera *m_camera;
};

#endif // PLAYER_H
