#include "GameEntity.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Shape.h"
#include "engine/world/World.h"

#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

#include <queue>
#include <vector>

GameEntity::GameEntity(World *world, Camera *camera,
                       glm::vec3 pos, glm::vec3 dims,
                       float speed, glm::vec3 vel, glm::vec3 acc,
                       glm::vec3 goal, float friction) :
    m_camera(camera),
    m_light(NULL),
    m_particleSystem(NULL),
    Entity(world, pos, dims, speed, vel, acc, goal, friction)
{
}

GameEntity::~GameEntity()
{
    delete m_light;
    delete m_particleSystem;
}

void GameEntity::startParticles()
{
    m_particleSystem->start();
}

void GameEntity::stopParticles()
{
    m_particleSystem->stop();
}

void GameEntity::onIntersect(Entity *ent, glm::vec3 mtv)
{
    return;
}

void GameEntity::onTick(float seconds)
{
    m_light->setPosition(m_pos);
    m_particleSystem->setTarget(m_pos);

    Entity::onTick(seconds);
}

void GameEntity::drawGeometry(Graphics *graphics)
{
    m_shape->draw(graphics);
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
    if(m_particleSystem && m_particleSystem->getActivated())
    {
        m_particleSystem->draw(graphics,
                               glm::mat4x4(glm::mat3x3(glm::inverse(m_camera->getView()))));
    }
}

void GameEntity::getLightGeometry(Graphics *graphics,
                                  std::priority_queue<std::pair<PointLight *,float>,
                                  std::vector<std::pair<PointLight *,float> >,
                                  CompareDepth> &depthQueue)
{
    if(m_light)
    {
        float dist = glm::max(glm::length(m_light->getPosition() - m_camera->getEye())
                - m_light->getRadius(), 0.f);

        std::pair<PointLight *, float> p(m_light, dist);
        depthQueue.push(p);
    }
}
