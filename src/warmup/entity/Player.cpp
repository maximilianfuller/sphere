#include "warmup/entity/Player.h"

#include "engine/world/World.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

#include "warmup/world/GameWorld.h"
#include "warmup/entity/Floor.h"
#include "warmup/entity/Zombie.h"
#include "warmup/entity/Bomb.h"

Player::Player(World *world, Camera *camera, float height) :
    m_camera(camera),
    // Movement
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    // Bomb placement
    m_cooldown(0),
    m_place(false),
    // Attributes
    m_yaw(0),
    m_pitch(0),
    m_height(height),
    // Constructors
    Entity(world),
    ActiveEntity(world, 5),
    WarmupEntity(world)
{
    /* Initialize camera */
    m_camera->setYaw(m_yaw);
    m_camera->setPitch(m_pitch);

    /* Create shape and bounding shape */
    m_shape = new Cylinder();
    m_boundingShape = new BoundingCylinder(m_pos, 0.5, m_height);

    /* Update shape and bounding shape to correspond to player's dimentions */
    updateShape();
    updateBoundingShape();
}

Player::~Player()
{
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

bool Player::getPlaceBomb()
{
    return m_place;
}

void Player::setPlaceBomb(bool val)
{
    m_place = val;
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

float Player::getHeight()
{
    return m_height;
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
}

void Player::placeBomb()
{
    m_world->addBackgroundEntity(new Bomb(m_world, m_pos));
    m_cooldown = 60;
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

void Player::updateShape()
{
    glm::vec3 pos = glm::vec3(m_pos.x, m_pos.y + m_height / 2, m_pos.z);
    glm::vec3 scale = glm::vec3(1, m_height, 1);

    glm::mat4x4 model = glm::mat4x4();
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);

    m_shape->setModelMatrix(model);
}

void Player::updateBoundingShape()
{
    BoundingCylinder *cyl = dynamic_cast<BoundingCylinder *>(m_boundingShape);
    cyl->setPosition(m_pos);
}

void Player::updateCamera()
{
    glm::vec3 pos = glm::vec3(m_pos.x, m_pos.y + m_height, m_pos.z);
    m_camera->setEye(pos);
}

void Player::onIntersect(Entity *ent, glm::vec3 mtv)
{
    dynamic_cast<WarmupEntity *>(ent)->onIntersect(this, mtv);
}

void Player::onIntersect(Floor *floor, glm::vec3 mtv)
{
    /* Reset velocity */
    m_pos.y = 0;
    m_vel.y = 0;

    /* Set grounded flag */
    m_grounded = true;

    /* Update shapes */
    updateShape();
    updateBoundingShape();
    updateCamera();
}

void Player::onIntersect(Zombie *zombie, glm::vec3 mtv)
{
    GameWorld *world = dynamic_cast<GameWorld *>(m_world);

    if(zombie->getGrounded() && mtv.x == 0 && mtv.z == 0)
    {
        m_pos.y = zombie->getHeight();
        m_vel.y = 0;
        m_grounded = true;
    }

    if(m_pos.y < 0.75 * zombie->getHeight())
    {
        world->setGameOver(true);
    }

    /* Update shapes */
    updateShape();
    updateBoundingShape();
    updateCamera();
}

void Player::onIntersect(Bomb *bomb, glm::vec3 mtv)
{
    if(bomb->getExploding())
    {
        m_vel -= 1.4f * glm::normalize(mtv);
        m_vel.y += 1.f;
        m_grounded = false;
    }
    else if(mtv.x == 0 && mtv.z == 0)
    {
        m_vel.y = 0;
        m_grounded = true;
    }

    /* Update shapes */
    updateShape();
    updateBoundingShape();
    updateCamera();
}

void Player::onTick(float seconds)
{
    /* Jump */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Place */
    if(m_place && m_pos.y == 0 && m_cooldown <= 0)
    {
        placeBomb();
    }

    m_cooldown--;

    /* Bounded screen */
    if(m_pos.x < -12 || m_pos.x > 12 || m_pos.z < -12 || m_pos.z > 12)
    {
        GameWorld *world = dynamic_cast<GameWorld *>(m_world);
        world->setGameOver(true);
    }

    /* Call superclass method to update player */
    ActiveEntity::onTick(seconds);

    /* Update camera */
    updateCamera();
}
