#include "engine/world/World.h"

#include "engine/graphics/Graphics.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/manager/Manager.h"
#include "engine/light/PointLight.h"
#include "engine/light/DirectionalLight.h"
#include "engine/particle/Particle.h"
#include "engine/particle/ParticleSystem.h"

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

Camera *World::getCamera()
{
    return m_camera;
}

int World::getNumEntities()
{
    return m_entities.size();
}

Entity *World::getEntity(int index)
{
    return m_entities[index];
}

QList<Entity *> World::getEntities()
{
    return m_entities;
}

void World::addEntity(Entity *ent)
{
    m_entities.append(ent);
}

void World::removeEntity(Entity *ent)
{
    delete ent;
    m_entities.removeAll(ent);
}

void World::removeEntities()
{
    foreach(Entity *e, m_entities)
    {
        if(m_toRemove.contains(e))
        {
            m_entities.removeOne(e);
            delete e;
        }
    }

    m_toRemove.clear();
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

void World::addParticle(glm::vec3 pos, glm::vec3 vel, float u, float v, QString textureKey)
{
    delete m_particles[m_particleIndex];
    m_particles[m_particleIndex++] = new Particle(pos, vel, u, v, textureKey);
    m_particleIndex %= 500;
}

void World::onTick(float seconds)
{
    foreach(Manager *manager, m_managers)
    {
        manager->onTick(seconds);
    }
    removeEntities();

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
    graphics->sendEmptyMatrices();
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

    /* Draw entity owned light geometry */
    foreach(Manager *manager, m_managers)
    {
        manager->drawLightGeometry(graphics);
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
