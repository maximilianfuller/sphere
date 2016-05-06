#include "GameEntity.h"

#include "engine/graphics/Graphics.h"
#include "engine/shape/Shape.h"
#include "engine/world/World.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Ellipsoid.h"

#include "engine/light/PointLight.h"

GameEntity::GameEntity(World *world,
                       float power, glm::vec3 color,
                       glm::vec3 pos, glm::vec3 dims,
                       float speed, glm::vec3 vel, glm::vec3 acc,
                       glm::vec3 goal, float friction) :
    m_power(power),
    m_time(0),
    m_light(NULL),
    m_warning(false),
    Entity(world, pos, dims, speed, vel, acc, goal, friction)
{
    /* Create shape */
    m_shape = new Ellipsoid(m_pos, m_dims);

    /* Create light */
    m_light = new PointLight(m_pos + glm::vec3(0, 1, 0), color);
}

GameEntity::~GameEntity()
{
    delete m_light;
}

float GameEntity::getRadius()
{
    return glm::pow(m_power * 5.f, 0.333f);
}

void GameEntity::setRadius(float radius)
{
    m_power = radius * 5;
}

float GameEntity::getLightRadius()
{
    return m_power;
}

glm::vec3 GameEntity::getLightColor()
{
    return m_light->getLightColor();
}

float GameEntity::getPower()
{
    return m_power;
}

void GameEntity::setPower(float power)
{
    m_power = power;
}

float GameEntity::getTransferRate(GameEntity *target)
{
    float dist = glm::length(target->getPosition() - m_pos);
    return (4 * m_power / m_targets.length()) / glm::max(dist, 1.f);
}

bool GameEntity::hasTarget(GameEntity* target)
{
    foreach(GameEntity *ent, m_targets)
    {
        if(ent == target)
            return true;
    }
}

void GameEntity::addTarget(GameEntity *target)
{
    m_targets.append(target);
}

int GameEntity::numTargets()
{
    return m_targets.length();
}

void GameEntity::clearTargets()
{
    m_targets.clear();
}

void GameEntity::onIntersect(Entity *ent, glm::vec3 mtv)
{
    return;
}

void GameEntity::onTick(float seconds)
{
    Entity::onTick(seconds);

    /* Update time to avoid floating point errors */
    m_time += seconds;

    if(m_time > 2 * M_PI)
    {
        m_time = 0;
    }

    /* Update light */
    m_shape->setPosition(m_pos + glm::vec3(0, 1, 0));
    m_light->setPosition(m_pos + glm::vec3(0, 1, 0));
    m_light->setRadius(m_power);

    /* Transfer matter */
    float delta = 0;

    // Absorb
    foreach(GameEntity *target, m_targets)
    {
        float amount = getTransferRate(target) * 0.002;

        delta += amount;
    }

    // Give
    foreach(GameEntity *target, m_targets)
    {
        float amount = target->getTransferRate(this) * 0.002;

        delta -= amount;
    }

    m_power += delta;

    /* Update warning */
    if(!m_warning && delta < 0)
    {
        if(m_time < 0.1 || glm::abs(2 * M_PI - m_time) < 0.1)
        {
            m_warning = true;
        }
    }

    if(m_warning && delta >= 0)
    {
        if(m_time < 0.1 || glm::abs(2 * M_PI - m_time) < 0.1)
        {
            m_warning = false;
        }
    }
}

void GameEntity::drawGeometry(Graphics *graphics)
{
}

void GameEntity::drawLights(Graphics *graphics)
{
    if(m_light)
    {
        if(m_warning)
        {
            float radius = m_light->getRadius();
            float newRadius = glm::max(radius * glm::cos(m_time), 0.f);

            m_light->setRadius(newRadius);
            m_light->draw(graphics);

            m_light->setRadius(radius);
        }
        else
        {
            m_light->draw(graphics);
        }
    }
}

void GameEntity::drawParticles(Graphics *graphics)
{
}

void GameEntity::drawLightGeometry(Graphics *graphics)
{
    if(m_light)
    {
        glm::vec3 pos = m_light->getPosition();

        /* Model matrix */
        float radius = getRadius();
        glm::vec3 scale = glm::vec3(radius, radius, radius);
        glm::mat4x4 model = glm::translate(glm::mat4x4(), pos) * glm::scale(glm::mat4x4(), scale);

        /* Updated color */
        glm::vec3 mixed = glm::mix(m_light->getIntensity(), glm::vec3(1), 0.5f);
        glm::vec4 color = glm::vec4(mixed, 1.f);

        // Warning color
        if(m_warning)
        {
            color.w = 0.6 + 0.4 * glm::cos(m_time);
        }

        /* Screen space position */
        Camera *cam = m_world->getCamera();
        glm::vec3 screenPos = glm::vec3(cam->getPerspective() * glm::vec4(pos, 1.0));

        /* Send uniforms */
        graphics->sendModelUniform(model);
        graphics->sendLightRadiusUniform(radius);
        graphics->sendLightPositionUniform(screenPos);
        graphics->sendColorUniform(color);
        graphics->sendTimeUniform(m_time);

        graphics->drawShape("sphere");
    }
}
