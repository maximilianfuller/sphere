#include "ParticleTube.h"

#include "engine/particle/Particle.h"
#include "engine/graphics/Graphics.h"
#include "engine/entity/Entity.h"

#include "platformer/entity/GameEntity.h"

ParticleTube::ParticleTube(QString textureKey,
                           glm::vec3 source, glm::vec3 target, glm::vec3 color,
                           float radius, float particleSize) :
    m_source(source),
    m_target(target),
    m_color(color),
    m_radius(radius),
    m_particleSize(particleSize),
    m_particleTimer(0),
    m_particleTimeout(5),
    ParticleSystem(textureKey)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i] = NULL;
    }
}

void ParticleTube::setColor(glm::vec3 color)
{
    m_color = color;
}

void ParticleTube::start()
{
    /* Create particles and set their age */
    if(!m_started && m_startTimer > 20)
    {
        m_started = true;
    }
    else if(!m_started)
    {
        m_startTimer++;
    }
}

void ParticleTube::stop()
{
    m_started = false;
}

bool ParticleTube::getStarted()
{
    return m_started;
}

void ParticleTube::createParticle()
{
    /* Random values to generate position and velocity */
    float rand_angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_vel = 0.5 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    /* Position on circle */
    float theta = 2 * M_PI * rand_angle;
    float u = rand_rad1 + rand_rad2;
    float radius = (u > 1 ? 2 - u : u);

    /* Particle position and velocity */
    glm::vec3 pos = glm::vec3(m_radius * glm::cos(theta), m_radius * glm::sin(theta), 0);
    glm::vec3 vel = glm::vec3(0, 0, -rand_vel);

    /* Create particle */
    delete m_particles[m_particleIndex];
    Particle *particle = new Particle(pos, vel, radius, theta, m_textureKey);
    m_particles[m_particleIndex++] = particle;
    m_particleIndex %= MAX_PARTICLES;
}

void ParticleTube::draw(Graphics *graphics, glm::mat4x4 look)
{
    /* Create new particle */
    if(m_particleTimer > m_particleTimeout)
    {
        createParticle();
        m_particleTimer = 0;
    }
    else
    {
        m_particleTimer++;
    }

    float distance = glm::length(m_target - m_source);
    glm::mat4x4 scale = glm::scale(glm::mat4x4(), glm::vec3(1, 1, distance));

    /* Align particle stream */
    glm::mat4x4 view = glm::lookAt(m_source, m_target, glm::normalize(m_source));
    glm::mat4x4 model = glm::inverse(view) * scale;

    /* Send color */
    graphics->sendColorUniform(glm::vec4(m_color, 1.0));

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        if(m_particles[i])
        {
            /* Particle expire by position */
            if(glm::abs(m_particles[i]->pos.z) >= 1)
            {
                delete(m_particles[i]);
                m_particles[i] = NULL;
                continue;
            }

            /* Particle expire by age */
            if(m_particles[i]->age >= MAX_AGE)
            {
                delete(m_particles[i]);
                m_particles[i] = NULL;
                createParticle();
                continue;
            }

            /* Tick and draw particle */
            m_particles[i]->tick(1.0 / 60.0);
            m_particles[i]->draw(graphics, look, model, 0.1);
        }
    }
}
