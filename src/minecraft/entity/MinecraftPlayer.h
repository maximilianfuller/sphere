#ifndef PLAYER_H
#define PLAYER_H

#include "engine/voxel/entity/VoxelEntity.h"

class Camera;
class MinecraftManager;

class MinecraftPlayer : public VoxelEntity
{
public:
    MinecraftPlayer(MinecraftManager *manager, Camera *camera);
    ~MinecraftPlayer();

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

    /* Update methods on tick */
    void updateFriction();
    void updateGoalVelocity();
    void updateAcceleration();

    void updateCamera();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);

    void onTick(float seconds);

private:
    Camera *m_camera;

    /* Movement */
    bool m_moveForward;
    bool m_moveBackward;
    bool m_moveLeft;
    bool m_moveRight;
    bool m_jump;

    /* Attributes */
    float m_yaw;
    float m_pitch;
};

#endif // PLAYER_H
