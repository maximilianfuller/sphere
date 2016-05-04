#include "ParticleStreamSystem.h"

#include "engine/particle/Particle.h"
#include "engine/graphics/Graphics.h"

ParticleStreamSystem::ParticleStreamSystem(QString textureKey,
                                           glm::vec3 source, glm::vec3 target, glm::vec3 color,
                                           float sourceRadius, float expireRadius,
                                           float startVel) :
    m_source(source),
    m_target(target),
    m_color(color),
    m_sourceRadius(sourceRadius),
    m_expireRadius(expireRadius),
    m_startVel(startVel),
    m_activated(false),
    m_stopTimer(40),
    ParticleSystem(textureKey)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i] = NULL;
    }
}

void ParticleStreamSystem::setSource(glm::vec3 source)
{
    m_source = source;
}

void ParticleStreamSystem::setTarget(glm::vec3 target)
{
    m_target = target;
}

void ParticleStreamSystem::setColor(glm::vec3 color)
{
    m_color = color;
}

void ParticleStreamSystem::setSourceRadius(float radius)
{
    m_sourceRadius = radius;
}

void ParticleStreamSystem::start()
{
    m_activated = true;
    m_stopTimer = 40;
}

void ParticleStreamSystem::stop()
{
    m_activated = false;
}

bool ParticleStreamSystem::getActivated()
{
    return !(m_stopTimer == 0 && !m_activated);
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
    float radius = m_sourceRadius * 0.4 * (u > 1 ? 2 - u : u);

    /* Circle rotation */
    glm::mat4x4 view = glm::lookAt(glm::vec3(0, 0, 0), m_target - m_source, glm::vec3(0, 1, 0));
    glm::mat4x4 model = glm::inverse(view);

    /* Create particle */
    glm::vec3 pos = glm::mat3x3(model)
            * glm::vec3(radius * glm::cos(theta), radius * glm::sin(theta), 0)
            + m_source;
    glm::vec3 vel = (rand_vel + m_startVel) * glm::normalize(m_target - m_source);

    delete m_particles[m_particleIndex];
    m_particles[m_particleIndex++] = new Particle(pos, vel, m_textureKey);
    m_particleIndex %= MAX_PARTICLES;
}

void ParticleStreamSystem::draw(Graphics *graphics, glm::mat4x4 model)
{
    /* Create a new particle */
    if(m_activated)
    {
        createParticle();
    }
    else
    {
        m_stopTimer--;
    }

    /* Send color */
    graphics->sendColorUniform(glm::vec4(m_color, 1.0));

    /* Update existing particles */
    glm::vec3 totalOffset = m_target - m_source;
    float totalDistance = glm::length(totalOffset);

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        if(m_particles[i])
        {
            glm::vec3 offset = m_particles[i]->pos - m_source;
            glm::vec3 offsetLeft = m_target - m_particles[i]->pos;

            float distance = glm::length(offset);

            if(distance + m_expireRadius >= totalDistance)
            {
                delete(m_particles[i]);
                m_particles[i] = NULL;
                continue;
            }

            if(m_activated)
            {
                float mag = glm::length(m_particles[i]->vel);
                m_particles[i]->vel = mag
                        * glm::normalize(m_particles[i]->vel
                                         + 5.f * offsetLeft * (distance / totalDistance));
            }
            else
            {
                if(m_stopTimer == 0)
                {
                    delete(m_particles[i]);
                    m_particles[i] = NULL;
                    continue;
                }

                float mag = glm::length(m_particles[i]->vel);
                m_particles[i]->vel = mag
                        * glm::normalize(m_particles[i]->vel
                                         + 0.3f * glm::vec3(0, -1, 0));
            }

            m_particles[i]->tick(1.0 / 60.0);
            m_particles[i]->draw(graphics, model);
        }
    }
}
