#ifndef PLAYER_H
#define PLAYER_H

#include "util/CommonIncludes.h"
#include "engine/entity/Entity.h"

namespace Graphics
{
class Controller;
}
class Camera;

const float RATE = 5.0;

const float JUMP_HEIGHT = 2;
const float JUMP_TIME = 0.5 * RATE;
const float G = -(2 * JUMP_HEIGHT) / (JUMP_TIME * JUMP_TIME);
const float JUMP_SPEED = (JUMP_HEIGHT - 0.5 * G * JUMP_TIME * JUMP_TIME) / JUMP_TIME;

const float MU_GROUND = 3.5;
const float MU_AIR = 0.5;

enum Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

class Player : public Entity
{
public:
    Player(Camera *camera, float height = 1.0);
    ~Player();

    bool getMoveFoward();
    bool getMoveBackward();
    bool getMoveLeft();
    bool getMoveRight();
    bool getJump();

    void setMoveFoward(bool val);
    void setMoveBackward(bool val);
    void setMoveLeft(bool val);
    void setMoveRight(bool val);
    void setJump(bool val);

    float getYaw();
    void setYaw(float yaw);

    float getPitch();
    void setPitch(float pitch);

    glm::vec3 getDirection();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getVelocity();
    void setVelocity(glm::vec3 vel);

    glm::vec3 getAcceleration();
    void setAcceleration(glm::vec3 acc);

    glm::vec3 getGoalVelocity();
    void setGoalVelocity(glm::vec3 goal);

    void rotate(float yaw, float pitch);

    void updateCamera();
    void updateShape();

    unsigned int getEntityType();
    bool hasIntersection(Entity *ent);
    void intersect(unsigned int e);
    void tick(float seconds);

private:
    Camera *m_camera;

    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveLeft;
    bool m_moveRight;
    bool m_jump;
    bool m_grounded;

    float m_height;
    float m_yaw;
    float m_pitch;

    glm::vec3 m_pos;
    glm::vec3 m_vel;
    glm::vec3 m_acc;
    glm::vec3 m_goal;
};

#endif // PLAYER_H
