#include "minecraft/entity/MinecraftPlayer.h"

#include "engine/voxel/manager/Manager.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

#include "engine/voxel/block/Block.h"

#include "minecraft/manager/MinecraftManager.h"

// NOTE: bouncing may happen if the frame rate is too low
MinecraftPlayer::MinecraftPlayer(MinecraftManager *manager, Camera *camera, float height) :
    m_camera(camera),
    // Movement
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_moveUp(false),
    m_moveDown(false),
    // Attributes
    m_yaw(0),
    m_pitch(0),
    m_height(height),
    // Constructors
    VoxelEntity(manager, 10.0),
    Entity(manager, glm::vec3(0, 32, 0))
{
    /* Initialize camera */
    m_camera->setYaw(m_yaw);
    m_camera->setPitch(m_pitch);

    /* Create shape and bounding shape */
    m_shape = new Cylinder();
    m_boundingShape = new BoundingCylinder(m_pos, m_dims);

    /* Update shape and bounding shape to correspond to player's dimentions */
    updateShape();
    updateBoundingShape();

    /* Set acceleration to zero */
    m_acc = glm::vec3(0, 0, 0);
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

bool MinecraftPlayer::getMoveUp()
{
    return m_moveUp;
}

void MinecraftPlayer::setMoveUp(bool val)
{
    m_moveUp = val;
}

bool MinecraftPlayer::getMoveDown()
{
    return m_moveDown;
}

void MinecraftPlayer::setMoveDown(bool val)
{
    m_moveDown = val;
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

float MinecraftPlayer::getHeight()
{
    return m_height;
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

void MinecraftPlayer::updateFriction()
{
    m_friction = MU_AIR;
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

    if(m_moveUp)
    {
        inputVel += glm::vec3(0, 1, 0);
    }

    if(m_moveDown)
    {
        inputVel += glm::vec3(0, -1, 0);
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

    m_acc = diff * m_friction;
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

void MinecraftPlayer::onIntersect(Block *block, glm::vec3 mtv)
{
    if(block->passable)
    {
        m_pos += mtv;

        updateShape();
        updateBoundingShape();
        updateCamera();
    }
}

void MinecraftPlayer::onTick(float seconds)
{
    /* Call superclass method to update player */
    VoxelEntity::onTick(seconds);

    /* Update camera */
    updateCamera();
}
