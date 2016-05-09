#include "platformer/entity/Player.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/world/World.h"
#include "engine/light/PointLight.h"
#include "engine/intersect/Ray.h"
#include "engine/shape/Ellipsoid.h"

#include "engine/particle/ParticleStreamSystem.h"

Player::Player(World *world, Camera *camera) :
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    m_nitro(false),
    m_attackTimer(0),
    m_camera(camera),
    GameEntity(world, 0.1, glm::vec3(0.8, 0.8, 1.0), glm::vec3(0, 3, 0), glm::vec3(1, 1, 1), 7)
{
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

glm::vec3 Player::getDirection()
{
    return glm::normalize(m_camera->getLook());
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

void Player::attack()
{
    if(m_attackTimer > 0)
        return;

    Ray ray = Ray(m_camera->getEye(), m_camera->getLook());
    CollisionData data;

    float minT = -1;
    GameEntity *minTarget = NULL;

    foreach(GameEntity *target, m_targets)
    {
        if(ray.intersectSphere(target->getLightPosition(), target->getRadius(), data))
        {
            if(minT < 0 || data.t < minT)
            {
                minT = data.t;
                minTarget = target;
            }
        }
    }

    if(minTarget)
    {
        minTarget->setStun();
        m_attackTimer = 120;
    }
}

void Player::updateGoalVelocity()
{
    /* Player direction */
    glm::vec3 dir = getDirection();
    glm::vec3 perp = glm::normalize(glm::cross(m_camera->getUp(), dir));

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
    if(glm::length2(inputVel) > 0)
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
    m_camera->setEye(m_pos);
}

void Player::onTick(float seconds)
{
    GameEntity::onTick(seconds);

    m_speed = 2.f*(glm::length(m_pos) - 1.f);

    /* Set jump velocity */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Update attack timer */
    if(m_attackTimer > 0)
    {
        m_attackTimer--;
    }

    /* Update camera */
    updateCamera();
}
