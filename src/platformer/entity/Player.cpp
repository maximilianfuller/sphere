#include "platformer/entity/Player.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/world/World.h"
#include "engine/light/PointLight.h"
#include "engine/intersect/Ray.h"
#include "engine/shape/Ellipsoid.h"
#include "engine/planet/planetmanager.h"

#include "engine/particle/ParticleStreamSystem.h"
#include "platformer/world/GameWorld.h"

Player::Player(World *world, Camera *camera) :
    m_moveForward(false),
    m_moveBackward(false),
    m_moveLeft(false),
    m_moveRight(false),
    m_jump(false),
    m_zoomIn(false),
    m_zoomOut(false),
    m_zoom(5),
    m_attackTimer(0),
    m_camera(camera),
    GameEntity(world, 0.002, glm::vec3(1, 1, 1), glm::vec3(1.0001, 0, 0), 7)
{
}

Player::~Player()
{
}

float Player::getSpeed()
{
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

bool Player::getZoomIn()
{
    return m_zoomIn;
}

void Player::setZoomIn(bool val)
{
    m_zoomIn = val;
}

bool Player::getZoomOut()
{
    return m_zoomOut;
}

void Player::setZoomOut(bool val)
{
    m_zoomOut = val;
}

float Player::getZoom()
{
    return m_zoom;
}

void Player::setZoom(float zoom)
{
    m_zoom = zoom;
}

glm::vec3 Player::getDirection()
{
    glm::vec3 look = glm::normalize(m_camera->getLook());
    glm::vec3 up = glm::normalize(m_pos);

    glm::vec3 dir = glm::normalize(look - glm::dot(look, up) * up);

    return dir - glm::dot(dir, up) * up;
}

void Player::jump()
{
    m_grounded = false;
    glm::vec3 up = glm::normalize(m_pos);
    glm::vec3 jump = up * JUMP_SPEED * 100.f;
    m_vel = m_vel - glm::dot(m_vel, up) * up + jump;
}

void Player::attack()
{
    if(m_attackTimer > 0)
    {
        return;
    }

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
    glm::vec3 up = glm::normalize(m_pos);
    glm::vec3 perp = glm::normalize(glm::cross(up, dir));

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
    float radius = getRadius();
    float dist = glm::max(m_zoom * radius, MIN_ZOOM);

    m_camera->setEye(m_pos - dist * m_camera->getLook());

    /*
    glm::vec3 eye = m_camera->getEye();

    GameWorld *world = dynamic_cast<GameWorld *>(m_world);
    float noise = world->getTerrainHeight(eye);

    if(glm::length(eye) - 0.0005f < noise)
    {
        m_camera->setEye(glm::normalize(eye) * (1.f + noise + 0.0005f));
    }
    */
}

void Player::onTick(float seconds)
{
    GameEntity::onTick(seconds);

    GameWorld *world = dynamic_cast<GameWorld *>(m_world);

    if(m_power <= 0 && !world->getStopped())
    {
        world->stop();
        return;
    }

    m_speed = .01f;

    /* Set jump velocity */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Set zoom */
    if(m_zoomIn && m_zoom * getRadius() > MIN_ZOOM)
    {
        m_zoom -= 0.03 * m_zoom;
    }

    if(m_zoomOut)
    {
        m_zoom += 0.03 * m_zoom;
    }

    /* Update attack timer */
    if(m_attackTimer > 0)
    {
        m_attackTimer--;
    }

    /* Update camera */
    updateCamera();
}

void Player::drawGeometry(Graphics *graphics)
{
    GameEntity::drawGeometry(graphics);
}

void Player::drawLightGeometry(Graphics *graphics)
{
    GameEntity::drawLightGeometry(graphics);
}
