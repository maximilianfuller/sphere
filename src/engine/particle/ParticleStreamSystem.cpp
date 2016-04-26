#include "ParticleStreamSystem.h"

#include "engine/particle/Particle.h"
#include "engine/graphics/Graphics.h"

ParticleStreamSystem::ParticleStreamSystem(QString textureKey,
                                           glm::vec3 start, glm::vec3 target,
                                           float startRadius, float expireRadius,
                                           float startVel) :
    m_start(start),
    m_target(target),
    m_startRadius(startRadius),
    m_expireRadius(expireRadius),
    m_startVel(startVel),
    ParticleSystem(textureKey)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i] = NULL;
    }
}

void ParticleStreamSystem::setStart(glm::vec3 start)
{
    m_start = start;
}

void ParticleStreamSystem::setTarget(glm::vec3 target)
{
    m_target = target;
}

void ParticleStreamSystem::createParticle()
{
    /* Random values to generate pos and vel */
    float rand_angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_vel = (m_startVel / 3.f)
            * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    /* Angle and radius */
    float theta = 2 * M_PI * rand_angle;
    float u = rand_rad1 + rand_rad2;
    float radius = m_startRadius * (u > 1 ? 2 - u : u);

    /* Circle rotation */
    glm::mat4x4 view = glm::lookAt(glm::vec3(0, 0, 0), m_target - m_start, glm::vec3(0, 1, 0));
    glm::mat4x4 model = glm::inverse(view);

    /* Create particle */
    glm::vec3 pos = glm::mat3x3(model)
            * glm::vec3(radius * glm::cos(theta), radius * glm::sin(theta), 0)
            + m_start;
    glm::vec3 vel = (rand_vel + m_startVel) * glm::normalize(m_target - m_start);

    delete m_particles[m_particleIndex];
    m_particles[m_particleIndex++] = new Particle(pos, vel, m_textureKey);
    m_particleIndex %= MAX_PARTICLES;
}

void ParticleStreamSystem::draw(Graphics *graphics, glm::mat4x4 model)
{
    /* Create a new particle */
    createParticle();

    /* Update existing particles */
    glm::vec3 totalOffset = m_target - m_start;
    float totalDistance = glm::length(totalOffset);

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        if(m_particles[i])
        {
            glm::vec3 offset = m_particles[i]->pos - m_start;
            glm::vec3 offsetLeft = m_target - m_particles[i]->pos;

            float distance = glm::length(offset);

            if(distance + m_expireRadius >= totalDistance)
            {
                delete(m_particles[i]);
                m_particles[i] = NULL;
                continue;
            }

            float mag = glm::length(m_particles[i]->vel);
            m_particles[i]->vel = mag
                    * glm::normalize(m_particles[i]->vel
                                     + 5.f * offsetLeft * (distance / totalDistance));

            m_particles[i]->tick(1.0 / 60.0);
            m_particles[i]->draw(graphics, model);
        }
    }
}
