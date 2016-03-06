#include "minecraft/entity/MinecraftPlayer.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

#include "engine/voxel/block/Block.h"

#include "minecraft/manager/MinecraftManager.h"

MinecraftPlayer::MinecraftPlayer(MinecraftManager *manager, Camera *camera) :
    m_camera(camera),
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    m_yaw(0),
    m_pitch(0),
    VoxelEntity(manager, 10.0),
    Entity(manager, glm::vec3(32, 80, 32), glm::vec3(0.8, 1, 0.8))
{
    /* Initialize camera */
    m_camera->setYaw(m_yaw);
    m_camera->setPitch(m_pitch);

    /* Create shape and bounding shape */
    m_shape = new Cylinder();

    /* Update shape and bounding shape to correspond to player's dimentions */
    updateShape();
    updateBoundingShape();
}

MinecraftPlayer::~MinecraftPlayer()
{
}

bool MinecraftPlayer::getMoveFoward()
{
    return m_moveForward;
}

void MinecraftPlayer::setMoveFoward(bool val)
{
    m_moveForward = val;
}

bool MinecraftPlayer::getMoveBackward()
{
    return m_moveBackward;
}

void MinecraftPlayer::setMoveBackward(bool val)
{
    m_moveBackward = val;
}

bool MinecraftPlayer::getMoveLeft()
{
    return m_moveLeft;
}

void MinecraftPlayer::setMoveLeft(bool val)
{
    m_moveLeft = val;
}

bool MinecraftPlayer::getMoveRight()
{
    return m_moveRight;
}

void MinecraftPlayer::setMoveRight(bool val)
{
    m_moveRight = val;
}

bool MinecraftPlayer::getJump()
{
    return m_jump;
}

void MinecraftPlayer::setJump(bool val)
{
    m_jump = val;
}

float MinecraftPlayer::getYaw()
{
    return m_yaw;
}

void MinecraftPlayer::setYaw(float yaw)
{
    m_yaw = yaw;
}

float MinecraftPlayer::getPitch()
{
    return m_pitch;
}

void MinecraftPlayer::setPitch(float pitch)
{
    m_pitch = pitch;
}

glm::vec3 MinecraftPlayer::getDirection()
{
    glm::vec3 dir = glm::vec3(glm::cos(m_yaw) * glm::cos(m_pitch), glm::sin(m_pitch),
                              glm::sin(m_yaw) * glm::cos(m_pitch));

    return glm::normalize(glm::vec3(dir.x, 0, dir.z));
}

void MinecraftPlayer::rotate(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);
    m_camera->rotate(yaw, pitch);
}

void MinecraftPlayer::jump()
{
    m_grounded = false;
    m_vel.y = JUMP_SPEED;
}

void MinecraftPlayer::updateFriction()
{
    m_friction = m_grounded ? MU_GROUND : MU_AIR;
}

void MinecraftPlayer::updateGoalVelocity()
{
    /* MinecraftPlayer direction */
    glm::vec3 dir = getDirection();
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    glm::vec3 inputVel = glm::vec3(0, 0, 0);

    /* Examine inputs */
    if(m_moveForward)
    {
        inputVel += dir;
    }

    if(m_moveBackward)
    {
        inputVel += -dir;
    }

    if(m_moveLeft)
    {
        inputVel += perp;
    }

    if(m_moveRight)
    {
        inputVel += -perp;
    }

    /* Set goal velocity */
    if(glm::length(inputVel) > 0)
    {
        m_goal = glm::normalize(inputVel);
    }
    else
    {
        m_goal = inputVel;
    }
}

void MinecraftPlayer::updateAcceleration()
{
    glm::vec3 diff = m_goal - m_vel;
    diff.x = m_friction * diff.x;
    diff.z = m_friction * diff.z;

    m_acc.x = diff.x;
    m_acc.z = diff.z;
}

void MinecraftPlayer::updateCamera()
{
    glm::vec3 pos = m_pos;
    pos.y += 0.5f * m_dims.y;
    m_camera->setEye(pos);
}

void MinecraftPlayer::onIntersect(Entity *ent, glm::vec3 mtv)
{
    ent->onIntersect(this, mtv);
}

void MinecraftPlayer::onTick(float seconds)
{
    /* Jump */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Call superclass method to update player */
    VoxelEntity::onTick(seconds);

    /* Update camera */
    updateCamera();
}
