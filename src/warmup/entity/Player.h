#ifndef PLAYER_H
#define PLAYER_H

#include "util/CommonIncludes.h"
#include "engine/entity/ActiveEntity.h"
#include "warmup/entity/WarmupEntity.h"

enum Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

class World;
class Camera;
class Floor;
class Zombie;

class Player : public ActiveEntity, WarmupEntity
{
public:
    Player(World *world, Camera *camera, float height = 1.0);
    ~Player();

    /* User control */
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

    bool getPlaceBomb();
    void setPlaceBomb(bool val);

    float getYaw();
    void setYaw(float yaw);

    float getPitch();
    void setPitch(float pitch);

    float getHeight();

    /* Camera direction */
    glm::vec3 getDirection();

    /* Actions */
    void rotate(float yaw, float pitch);
    void jump();
    void placeBomb();

    /* Update methods on tick */
    void updateFriction();
    void updateGoalVelocity();
    void updateAcceleration();

    void updateShape();
    void updateBoundingShape();
    void updateCamera();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);
    void onIntersect(Floor *floor, glm::vec3 mtv);
    void onIntersect(Zombie *zombie, glm::vec3 mtv);
    void onIntersect(Bomb *bomb, glm::vec3 mtv);

    void onTick(float seconds);

private:
    Camera *m_camera;

    /* Movement */
    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveLeft;
    bool m_moveRight;
    bool m_jump;

    /* Bomb placement */
    int m_cooldown;
    bool m_place;

    /* Attributes */
    float m_height;
    float m_yaw;
    float m_pitch;
};

#endif // PLAYER_H
