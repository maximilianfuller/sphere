#include "warmup/entity/Player.h"

#include "engine/camera/Camera.h"
#include "engine/graphics/Controller.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

Player::Player(Camera *camera, float height) :
    m_camera(camera),
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    m_grounded(true),
    m_yaw(0),
    m_pitch(0),
    m_height(height),
    m_goal(0, 0, 0)
{
    m_camera->setYaw(m_yaw);
    m_camera->setPitch(m_pitch);
    m_shape = new Cylinder();
    m_boundingShape = new BoundingCylinder(m_pos, m_height, 1.0);
}

Player::~Player()
{
}

bool Player::getMoveFoward()
{
    return m_moveForward;
}

bool Player::getMoveBackward()
{
    return m_moveBackward;
}

bool Player::getMoveLeft()
{
    return m_moveLeft;
}

bool Player::getMoveRight()
{
    return m_moveRight;
}

bool Player::getJump()
{
    return m_jump;
}

void Player::setMoveFoward(bool val)
{
    m_moveForward = val;
}

void Player::setMoveBackward(bool val)
{
    m_moveBackward = val;
}

void Player::setMoveLeft(bool val)
{
    m_moveLeft = val;
}

void Player::setMoveRight(bool val)
{
    m_moveRight = val;
}

void Player::setJump(bool val)
{
    m_jump = val;
}

void Player::rotate(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);
    m_camera->rotate(yaw, pitch);
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

glm::vec3 Player::getPosition()
{
    return m_pos;
}

void Player::setPosition(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 Player::getVelocity()
{
    return m_vel;
}

void Player::setVelocity(glm::vec3 vel)
{
    m_vel = vel;
}

glm::vec3 Player::getAcceleration()
{
    return m_acc;
}

void Player::setAcceleration(glm::vec3 acc)
{
    m_acc = acc;
}

glm::vec3 Player::getGoalVelocity()
{
    return m_goal;
}

void Player::setGoalVelocity(glm::vec3 goal)
{
    m_goal = goal;
}

void Player::updateCamera()
{
    glm::vec3 pos = glm::vec3(m_pos.x, m_pos.y + m_height, m_pos.z);
    m_camera->setEye(pos);
}

void Player::updateShape()
{
    glm::vec3 pos = glm::vec3(m_pos.x, m_pos.y + m_height / 2, m_pos.z);

    glm::mat4x4 model = glm::mat4x4();
    model = glm::translate(model, pos);

    m_shape->setModelMatrix(model);
}

void Player::updateBoundingShape()
{
    BoundingCylinder *cyl = dynamic_cast<BoundingCylinder *>(m_boundingShape);
    cyl->setPosition(m_pos);
}

void Player::onIntersect(Entity *ent, glm::vec3 mtv)
{
    /* Reset height, velocity, and acceleration */
    m_pos.y = 0;
    m_vel.y = 0;
    m_acc.y = 0;

    /* Set grounded flag */
    m_grounded = true;
}

void Player::onTick(float seconds)
{
    // Player direction
    glm::vec3 dir = getDirection();
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

    glm::vec3 inputVel = glm::vec3(0, 0, 0);
    int numInputs = 0;

    // Examine inputs
    if(m_moveForward)
    {
        inputVel += dir;
        numInputs++;
    }

    if(m_moveBackward)
    {
        inputVel += -dir;
        numInputs++;
    }

    if(m_moveLeft)
    {
        inputVel += perp;
        numInputs++;
    }

    if(m_moveRight)
    {
        inputVel += -perp;
        numInputs++;
    }

    if(m_jump && m_grounded)
    {
        m_grounded = false;
        m_vel.y = JUMP_SPEED;
        m_acc.y = G;
    }

    // Set goal velocity
    if(glm::length(inputVel) > 0)
    {
        m_goal = glm::normalize(inputVel);
    }
    else
    {
        m_goal = inputVel;
    }

    // Friction
    float friction = m_grounded ? MU_GROUND : MU_AIR;

    // Acceleration
    glm::vec3 diff = m_goal - m_vel;
    diff.x = friction * diff.x;
    diff.z = friction * diff.z;

    m_acc.x = diff.x;
    m_acc.z = diff.z;

    // Velocity
    m_vel += RATE * m_acc * seconds;
    m_pos += RATE * m_vel * seconds;

    // Update camera and shape
    updateCamera();
    updateShape();
    updateBoundingShape();
}
