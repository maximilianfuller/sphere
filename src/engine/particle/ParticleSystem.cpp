#include "ParticleSystem.h"

#include "engine/particle/Particle.h"
#include "engine/graphics/Graphics.h"

ParticleSystem::ParticleSystem(QString textureKey) :
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

void ParticleSystem::tick(float seconds)
{
    float rand_angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_vel = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    float theta = 2 * M_PI * rand_angle;
    float u = rand_rad1 + rand_rad2;
    float radius = u > 1 ? 2 - u : u;

    glm::vec3 pos = glm::vec3(radius * glm::cos(theta), radius * glm::sin(theta) + 3, -10);
    glm::vec3 vel = glm::vec3(0, 0, rand_vel + 1.0);

    delete m_particles[m_particleIndex];
    m_particles[m_particleIndex++] = new Particle(pos, vel, m_textureKey);
    m_particleIndex %= MAX_PARTICLES;
}

void ParticleSystem::draw(Graphics *graphics)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        if(m_particles[i])
        {
            m_particles[i]->tick(1.0 / 60.0);
            m_particles[i]->draw(graphics);
        }
    }
}
