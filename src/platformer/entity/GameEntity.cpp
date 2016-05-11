#include "GameEntity.h"

#include "engine/graphics/Graphics.h"
#include "engine/shape/Shape.h"
#include "engine/world/World.h"
#include "engine/camera/Camera.h"

#include "engine/light/PointLight.h"

GameEntity::GameEntity(World *world,
                       float power, glm::vec3 color, glm::vec3 pos,
                       float speed, glm::vec3 vel, glm::vec3 acc,
                       glm::vec3 goal, float friction) :
    m_power(power),
    m_time(0),
    m_delta(0),
    m_light(NULL),
    m_warning(false),
    m_warningTimer(0),
    m_stun(false),
    m_stunTimer(0),
    Entity(world, pos, glm::vec3(0, 0, 0), speed, vel, acc, goal, friction)
{
    /* Create shape */
    m_shape = NULL;

    /* Create light */
    m_light = new PointLight(m_pos, color);
    m_light->setRadius(getLightRadius());
}

GameEntity::~GameEntity()
{
    delete m_light;
}

float GameEntity::getRadius()
{
    return glm::pow(m_power * .0000005f, 0.333f);
}

float GameEntity::getLightRadius()
{
    return getRadius() * 20.0;
}

glm::vec3 GameEntity::getLightPosition()
{
    return m_light->getPosition();
}

glm::vec3 GameEntity::getLightIntensity()
{
    return m_light->getIntensity();
}

glm::vec3 GameEntity::getColor()
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

float GameEntity::getDelta()
{
    return m_delta;
}

bool GameEntity::getStun()
{
    return m_stun;
}

void GameEntity::setStun()
{
    m_stun = true;
    m_stunTimer = 0;
}

float GameEntity::getTransferRate(GameEntity *target)
{
    if(!m_stun)
    {
        float dist = glm::length(target->getPosition() - m_pos);
        float transfer = (glm::pow(m_power, 0.333f)) / glm::max(dist, 1.f);

        if(target->getPower() < m_power && target->getPower() >= 0.002)
        {
            return glm::clamp(transfer, 0.f, glm::max(target->getPower() * MAX_TRANSFER, 0.f));
        }
        else if(target->getPower() > m_power && target->getPower() >= 0.002)
        {
            return glm::clamp(transfer, 0.f, glm::max(m_power * MAX_TRANSFER, 0.f));
        }
        else if(target->getPower() < m_power)
        {
            return glm::clamp(transfer, 0.f, 0.5f);
        }
    }
    else
    {
        return 0;
    }
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

void GameEntity::updateAcceleration()
{
    glm::vec3 up = glm::normalize(m_pos);
    glm::vec3 perpVel = m_vel - glm::dot(up, m_vel) * up;
    glm::vec3 diff = m_goal - perpVel;

    m_acc = glm::normalize(m_pos) * G;
    m_acc += m_friction * diff;
}

void GameEntity::updateVelocity(float seconds)
{
    glm::vec3 up = glm::normalize(m_pos);

    if(m_grounded && glm::dot(m_vel, up) < 0)
    {
        m_vel = m_vel - glm::dot(up, m_vel) * up;
    }

    m_vel += m_acc * seconds;
}

void GameEntity::updatePosition(float seconds)
{
    if(!m_moved)
    {
        glm::vec3 up = glm::normalize(m_pos);
        glm::vec3 downVel = glm::dot(up, m_vel) * up;

        m_pos += (m_speed * (m_vel - downVel) + downVel) * seconds;
    }

    m_moved = false;
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

    /* Update stun */
    if(m_stunTimer < 60)
    {
        m_stunTimer++;
    }
    else
    {
        m_stun = false;
        m_stunTimer = 0;
    }

    /* Update light */
    m_light->setPosition(m_pos);
    m_light->setRadius(getLightRadius());

    /* Transfer matter */
    m_delta = 0;
    glm::vec3 lightInt = getLightIntensity();
    float intensity = glm::length(lightInt);

    foreach(GameEntity *target, m_targets)
    {
        float amount = getTransferRate(target) * TRANSFER_RATE;
        lightInt += target->getLightIntensity() * getTransferRate(target) * 0.05f;

        m_delta += amount;
    }

    foreach(GameEntity *target, m_targets)
    {
        float amount = target->getTransferRate(this) * TRANSFER_RATE;
        lightInt -= target->getLightIntensity() * target->getTransferRate(this) * 0.05f;

        m_delta -= amount;
    }

    m_light->setIntensity(intensity * glm::normalize(lightInt));

    m_power += m_delta;
    m_power = glm::max(m_power, 0.f);
}

void GameEntity::drawGeometry(Graphics *graphics)
{
}

void GameEntity::drawLights(Graphics *graphics)
{
    m_light->draw(graphics);
}

void GameEntity::drawParticles(Graphics *graphics)
{
}

void GameEntity::drawLightGeometry(Graphics *graphics)
{
    if(m_light)
    {
        /* Model matrix */
        glm::vec3 pos = m_light->getPosition();
        float radius = getRadius();

        glm::vec3 scale = glm::vec3(radius, radius, radius);
        glm::mat4x4 model = glm::translate(glm::mat4x4(), pos) * glm::scale(glm::mat4x4(), scale);

        /* Updated color */
        glm::vec4 color = glm::vec4(glm::mix(m_light->getIntensity(), glm::vec3(1), 0.5f), 1);

        // Stun color
        if(m_stun)
        {
            float mix = glm::smoothstep(0.f, 60.f, float(m_stunTimer));
            color = glm::mix(glm::vec4(1, 1, 1, 1), color, mix);
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
