#include "platformer/entity/Player.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"

#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

Player::Player(World *world, Camera *camera) :
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    m_nitro(false),
    m_absorb(false),
    m_yaw(0),
    m_pitch(0),
    m_camera(camera),
    GameEntity(world, 20.0, glm::vec3(0.8, 0.8, 1.0), glm::vec3(0, 2.0, 0), glm::vec3(1, 1, 1), 7)
{
    /* Initialize camera */
    m_camera->setYaw(m_yaw);
    m_camera->setPitch(m_pitch);
}

Player::~Player()
{
}

float Player::getSpeed()
{
    if(m_nitro)
    {
        return m_speed * 2.0;
    }

    return m_speed;
}

bool Player::getMoveFoward()
{
    return m_moveForward;
}

void Player::setMoveFoward(bool val)
{
    m_moveForward = val;
}

bool Player::getMoveBackward()
{
    return m_moveBackward;
}

void Player::setMoveBackward(bool val)
{
    m_moveBackward = val;
}

bool Player::getMoveLeft()
{
    return m_moveLeft;
}

void Player::setMoveLeft(bool val)
{
    m_moveLeft = val;
}

bool Player::getMoveRight()
{
    return m_moveRight;
}

void Player::setMoveRight(bool val)
{
    m_moveRight = val;
}

bool Player::getJump()
{
    return m_jump;
}

void Player::setJump(bool val)
{
    m_jump = val;
}

bool Player::getNitro()
{
    return m_nitro;
}

void Player::setNitro(bool val)
{
    m_nitro = val;
}

bool Player::getAbsorb()
{
    return m_absorb;
}

void Player::setAbsorb(bool val)
{
    m_absorb = val;
}

float Player::getYaw()
{
    return m_yaw;
}

void Player::setYaw(float yaw)
{
    m_yaw = yaw;
}

float Player::getPitch()
{
    return m_pitch;
}

void Player::setPitch(float pitch)
{
    m_pitch = pitch;
}

glm::vec3 Player::getDirection()
{
    glm::vec3 dir = glm::vec3(glm::cos(m_yaw) * glm::cos(m_pitch), glm::sin(m_pitch),
                              glm::sin(m_yaw) * glm::cos(m_pitch));

    return glm::normalize(glm::vec3(dir.x, 0, dir.z));
}

void Player::rotate(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);
    m_camera->rotate(yaw, pitch);
}

void Player::jump()
{
    m_grounded = false;
    m_vel.y = JUMP_SPEED;

    if(m_nitro)
    {
        m_vel.y *= 2.2;
    }
}

void Player::updateGoalVelocity()
{
    /* Player direction */
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

void Player::updateCamera()
{
    glm::vec3 pos = m_pos;
    pos.y += m_dims.y;

    m_camera->setEye(pos);
}

void Player::tryConnect(GameEntity *entity)
{
    float radius = m_light->getRadius();

    if(glm::length2(m_pos - entity->getPosition()) < radius * radius && m_absorb)
    {
        setConnected(true);
        entity->onConnected(this);

        /* Set up connection */
        m_stream->setSource(entity->getPosition() + glm::vec3(0, 1, 0));
        m_stream->setColor(entity->getLightColor());
        m_stream->setSourceRadius(entity->getRadius() / 2.f);

        transferPower(entity);
    }
}

void Player::onConnected(GameEntity *entity)
{
    return;
}

void Player::onTick(float seconds)
{
    GameEntity::onTick(seconds);

    /* Set jump velocity */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Update camera */
    updateCamera();
}
