#include "GameEntity.h"

#include "engine/graphics/Graphics.h"
#include "engine/shape/Shape.h"
#include "engine/world/World.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Ellipsoid.h"

#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

GameEntity::GameEntity(World *world,
                       float power, glm::vec3 color,
                       glm::vec3 pos, glm::vec3 dims,
                       float speed, glm::vec3 vel, glm::vec3 acc,
                       glm::vec3 goal, float friction) :
    m_power(power),
    m_light(NULL),
    m_stream(NULL),
    m_connected(true),
    Entity(world, pos, dims, speed, vel, acc, goal, friction)
{
    /* Create shape */
    m_shape = new Ellipsoid(m_pos, m_dims);

    /* Create light */
    m_light = new PointLight(m_pos + glm::vec3(0, 1, 0), color);

    /* Create particle system */
    m_stream = new ParticleStreamSystem("particle", glm::vec3(0, 0, 0), m_pos,
                                        color, 2.0, 0.5, 7.f);
}

GameEntity::~GameEntity()
{
    delete m_light;
    delete m_stream;
}

float GameEntity::getPower()
{
    return m_power;
}

void GameEntity::setPower(float power)
{
    m_power = power;
}

bool GameEntity::getConnected()
{
    return m_connected;
}

void GameEntity::setConnected(bool connected)
{
    m_connected = connected;
}

float GameEntity::getRadius()
{
    return m_shape->getDimensions().x * 2;
}

void GameEntity::setRadius(float radius)
{
    m_shape->setDimensions(glm::vec3(radius * 2, radius * 2, radius * 2));
}

glm::vec3 GameEntity::getLightColor()
{
    return m_light->getLightColor();
}

float GameEntity::getTransferRate()
{
    float rate = glm::smoothstep(1.f, 100.f, m_power) * 0.1;
    return glm::max(rate, 0.005f);
}

void GameEntity::tryConnect(GameEntity *entity)
{
}

void GameEntity::onConnected(GameEntity *entity)
{
}

void GameEntity::transferPower(GameEntity *entity)
{
    /* Transfer power */
    float rate = getTransferRate();

    if(entity->getPower() > 0)
    {
        entity->setPower(entity->getPower() - rate);
        setPower(m_power + rate);
    }
}

void GameEntity::startStream()
{
    m_stream->start();
}

void GameEntity::stopStream()
{
    m_stream->stop();
}

void GameEntity::onIntersect(Entity *ent, glm::vec3 mtv)
{
    return;
}

void GameEntity::onTick(float seconds)
{
    Entity::onTick(seconds);

    m_shape->setPosition(m_pos + glm::vec3(0, 1, 0));
    m_light->setPosition(m_pos + glm::vec3(0, 1, 0));
    m_light->setRadius(m_power);
    m_stream->setTarget(m_light->getPosition());
}

void GameEntity::drawGeometry(Graphics *graphics)
{
}

void GameEntity::drawLights(Graphics *graphics)
{
    if(m_light)
    {
        m_light->draw(graphics);
    }
}

void GameEntity::drawParticles(Graphics *graphics)
{
    Camera *camera = m_world->getCamera();

    if(m_connected)
    {
        m_stream->start();
    }
    else
    {
        m_stream->stop();
    }

    if(m_stream && m_stream->getActivated())
    {
        m_stream->draw(graphics,
                       glm::mat4x4(glm::mat3x3(glm::inverse(camera->getView()))));
    }
}

void GameEntity::drawLightGeometry(Graphics *graphics)
{
    if(m_light)
    {
        glm::vec3 pos = m_shape->getPosition();

        /* Model matrix */
        float radius = getRadius();
        glm::vec3 scale = glm::vec3(radius, radius, radius);
        glm::mat4x4 model = glm::translate(glm::mat4x4(), pos) * glm::scale(glm::mat4x4(), scale);

        /* Updated color */
        glm::vec3 mixed = glm::mix(m_light->getIntensity(), glm::vec3(1), 0.5f);
        glm::vec4 color = glm::vec4(mixed, glm::min(m_power / 100.f, 1.f));

        /* Send uniforms */
        graphics->sendModelUniform(model);
        graphics->sendLightRadiusUniform(radius);
        graphics->sendLightPositionUniform(pos);
        graphics->sendColorUniform(color);

        graphics->drawShape("sphere");
    }
}
