#include "engine/world/World.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/manager/Manager.h"
#include "engine/light/PointLight.h"
#include "engine/light/DirectionalLight.h"
#include "engine/particle/Particle.h"
#include "engine/particle/ParticleSystem.h"

#include <queue>
#include <vector>

World::World(Camera *camera) :
    m_camera(camera)
{
    for(int i = 0; i < 500; i++)
    {
        m_particles[i] = NULL;
    }
}

World::~World()
{
    foreach(Entity *ent, m_entities)
    {
        delete(ent);
    }

    foreach(Manager *manager, m_managers)
    {
        delete(manager);
    }

    foreach(PointLight *light, m_pointLights)
    {
        delete(light);
    }

    foreach(DirectionalLight *light, m_directionalLights)
    {
        delete(light);
    }

    for(int i = 0; i < 500; i++)
    {
        delete(m_particles[i]);
    }
}

int World::getNumEntities()
{
    return m_entities.size();
}

Entity *World::getEntity(int index)
{
    return m_entities[index];
}

void World::addEntity(Entity *ent)
{
    m_entities.append(ent);
}

void World::removeEntity(Entity *ent)
{
    int i = 0;

    foreach(Entity *e, m_entities)
    {
        if(ent == e)
        {
            break;
        }

        i++;
    }

    delete m_entities[i];
    m_entities.removeAt(i);
}

void World::addManager(Manager *manager)
{
    m_managers.append(manager);
}

PointLight *World::getPointLight(int index)
{
    return m_pointLights[index];
}

void World::addPointLight(PointLight *light)
{
    m_pointLights.append(light);
}

void World::removePointLight(PointLight *light)
{
    int i = 0;

    foreach(PointLight *l, m_pointLights)
    {
        if(light == l)
        {
            break;
        }

        i++;
    }

    delete m_pointLights[i];
    m_pointLights.removeAt(i);
}

DirectionalLight *World::getDirectionalLight(int index)
{
    return m_directionalLights[index];
}

void World::addDirectionalLight(DirectionalLight *light)
{
    m_directionalLights.append(light);
}

void World::removeDirectionalLight(DirectionalLight *light)
{
    int i = 0;

    foreach(DirectionalLight *l, m_directionalLights)
    {
        if(light == l)
        {
            break;
        }

        i++;
    }

    delete m_directionalLights[i];
    m_directionalLights.removeAt(i);
}

Particle *World::getParticle(int index)
{
    return m_particles[index];
}

void World::addParticle(glm::vec3 pos, glm::vec3 vel, QString textureKey)
{
    delete m_particles[m_particleIndex];
    m_particles[m_particleIndex++] = new Particle(pos, vel, textureKey);
    m_particleIndex %= 500;
}

void World::onTick(float seconds)
{
    foreach(Manager *manager, m_managers)
    {
        manager->onTick(seconds);
    }
}

void World::drawGeometry(Graphics *graphics)
{
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    foreach(Manager *manager, m_managers)
    {
        manager->drawGeometry(graphics);
    }
}

void World::drawLights(Graphics *graphics)
{
    /* Draw point lights */
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    foreach(PointLight *light, m_pointLights)
    {
        light->draw(graphics);
    }

    foreach(Manager *manager, m_managers)
    {
        manager->drawLights(graphics);
    }

    /* Draw directional lights */
    graphics->sendEmptyMatrices();

    foreach(DirectionalLight *light, m_directionalLights)
    {
        light->draw(graphics);
    }
}

void World::drawParticles(Graphics *graphics)
{
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    graphics->sendColorUniform(glm::vec4(1));
    graphics->sendUseLightingUniform(0);
    graphics->sendUseTextureUniform(1);

    /* Draw entity owned particle systems */
    foreach(Manager *manager, m_managers)
    {
        manager->drawParticles(graphics);
    }
}

void World::drawLightGeometry(Graphics *graphics)
{
    /* Draw point lights */
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    std::priority_queue<std::pair<PointLight *,float>,
            std::vector<std::pair<PointLight *,float> >, CompareDepth> depthQueue;

    foreach(Manager *manager, m_managers)
    {
        manager->getLightGeometry(graphics, depthQueue);
    }

    foreach(PointLight *light, m_pointLights)
    {
        float dist = glm::max(glm::length(light->getPosition() - m_camera->getEye())
                - light->getRadius(), 0.f);

        std::pair<PointLight *, float> p(light, dist);

        depthQueue.push(p);
    }

    while(!depthQueue.empty())
    {
        (depthQueue.top()).first->drawGeometry(graphics);
        depthQueue.pop();
    }
}

void World::mousePressEvent(QMouseEvent *event)
{
}

void World::mouseMoveEvent(QMouseEvent *event, int startX,
                           int startY)
{
}

void World::mouseReleaseEvent(QMouseEvent *event)
{
}

void World::wheelEvent(QWheelEvent *event)
{
}

void World::keyPressEvent(QKeyEvent *event)
{
}

void World::keyReleaseEvent(QKeyEvent *event)
{
}
