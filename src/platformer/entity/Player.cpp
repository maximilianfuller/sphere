#include "platformer/entity/Player.h"

#include "engine/graphics/Controller.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Ellipsoid.h"
#include "engine/intersect/BoundingCylinder.h"

Player::Player(World *world, Camera *camera) :
    m_camera(camera),
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    m_nitro(false),
    m_yaw(0),
    m_pitch(0),
    Entity(world, glm::vec3(0, 2.0, 0), glm::vec3(0.5, 1, 0.5), 7)
{
    /* Initialize camera */
    m_camera->setYaw(m_yaw);
    m_camera->setPitch(m_pitch);

    /* Create shape and bounding shape */
    m_shape = new Ellipsoid(m_pos, m_dims);

    /* Update shape and bounding shape to correspond to player's dimentions */
    updateShape();
    updateBoundingShape();
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

void Player::updateFriction()
{
    m_friction = m_grounded ? MU_GROUND : MU_AIR;
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

void Player::updateAcceleration()
{
    glm::vec3 diff = m_goal - m_vel;
    diff.x = m_friction * diff.x;
    diff.z = m_friction * diff.z;

    m_acc.x = diff.x;
    m_acc.z = diff.z;
}

void Player::updateCamera()
{
    glm::vec3 pos = m_pos;
    pos.y += m_dims.y;

    m_camera->setEye(pos);
}

void Player::onIntersect(Entity *ent, glm::vec3 mtv)
{
    return;
}

void Player::onTick(float seconds)
{
    /* Jump */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Call superclass method to update player */
    Entity::onTick(seconds);

    /* Update camera */
    updateCamera();
}

void Player::onDraw(Graphics::Controller *graphics)
{
    if(m_camera->getThirdPerson())
    {
        m_shape->draw(graphics);
    }
}
