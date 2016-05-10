#include "ParticleSystem.h"

#include "engine/particle/Particle.h"
#include "engine/graphics/Graphics.h"

ParticleSystem::ParticleSystem(QString textureKey) :
    m_particleIndex(0),
    m_textureKey(textureKey)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i] = NULL;
    }
}

ParticleSystem::~ParticleSystem()
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        delete(m_particles[i]);
    }
}

void ParticleSystem::draw(Graphics *graphics, glm::mat4x4 model)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        if(m_particles[i])
        {
            m_particles[i]->tick(1.0 / 60.0);
            m_particles[i]->draw(graphics, model, glm::mat4x4());
        }
    }
}
