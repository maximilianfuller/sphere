#include "ParticleStreamSystem.h"

#include "engine/particle/Particle.h"
#include "engine/graphics/Graphics.h"
#include "engine/entity/Entity.h"

#include "platformer/entity/GameEntity.h"

ParticleStreamSystem::ParticleStreamSystem(QString textureKey,
                                           Entity *source, Entity *target, glm::vec3 color,
                                           float particleSize) :
    m_source(source),
    m_target(target),
    m_color(color),
    m_particleSize(particleSize),
    m_particleTimer(0),
    m_particleTimeout(0),
    m_started(false),
    m_startTimer(0),
    ParticleSystem(textureKey)
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i] = NULL;
    }
}

Entity *ParticleStreamSystem::getSource()
{
    return m_source;
}

void ParticleStreamSystem::setSource(Entity *ent)
{
    m_source = ent;
}

Entity *ParticleStreamSystem::getTarget()
{
    return m_target;
}

void ParticleStreamSystem::setTarget(Entity *ent)
{
    m_target = ent;
}

void ParticleStreamSystem::setColor(glm::vec3 color)
{
    m_color = color;
}

void ParticleStreamSystem::start()
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

void ParticleStreamSystem::stop()
{
    m_started = false;
}

bool ParticleStreamSystem::getStarted()
{
    return m_started;
}

void ParticleStreamSystem::createParticle()
{
    GameEntity *source = dynamic_cast<GameEntity *>(m_source);
    GameEntity *target = dynamic_cast<GameEntity *>(m_target);

    /* Random values to generate position and velocity */
    float rand_angle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_rad2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_vel = 0.5 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand_dist = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    /* Position on circle */
    float theta = 2 * M_PI * rand_angle;
    float u = rand_rad1 + rand_rad2;
    float radius = (u > 1 ? 2 - u : u);

    float sourceRadius = source->getRadius() * 0.2 * radius;
    float targetRadius = target->getRadius() * 0.2 * radius;

    /* Particle position and velocity */
    glm::vec3 pos, vel;

    // Set depending on relative size of source and target
    if(target->getTransferRate(source) < source->getTransferRate(target))
    {
        pos = glm::vec3(targetRadius * glm::cos(theta), targetRadius * glm::sin(theta), -1);
        vel = glm::vec3(0, 0, rand_vel);
    }
    else
    {
        pos = glm::vec3(sourceRadius * glm::cos(theta), sourceRadius * glm::sin(theta), 0);
        vel = glm::vec3(0, 0, -rand_vel);
    }

    /* Create particle */
    delete m_particles[m_particleIndex];
    Particle *particle = new Particle(pos, vel, radius, theta, m_textureKey);
    m_particles[m_particleIndex++] = particle;
    m_particleIndex %= MAX_PARTICLES;
    particle->pos.z = -rand_dist;
}

void ParticleStreamSystem::draw(Graphics *graphics, glm::mat4x4 look)
{
    if(!m_started)
    {
        return;
    }

    GameEntity *source = dynamic_cast<GameEntity *>(m_source);
    GameEntity *target = dynamic_cast<GameEntity *>(m_target);

    /* Create new particle */
    if(m_particleTimer > m_particleTimeout)
    {
        createParticle();
        m_particleTimer = 0;

        if(source->getTransferRate(target) - target->getTransferRate(source) != 0)
        {
            m_particleTimeout = int(glm::min(0.005f / glm::abs(source->getTransferRate(target) - target->getTransferRate(source)), 120.f));
        }
        else
        {
            m_particleTimeout = 120;
        }
    }
    else
    {
        m_particleTimer++;
    }

    /* Update existing particles */
    glm::vec3 sourcePos = m_source->getPosition();
    glm::vec3 targetPos = m_target->getPosition();

    float totalDistance = glm::max(glm::length(targetPos - sourcePos), 0.0001f);
    float maxDistance = (target->getRadius() + source->getRadius()) * TRANSFER_SCALE;
    glm::mat4x4 scale = glm::scale(glm::mat4x4(), glm::vec3(1, 1, totalDistance));

    /* Align particle stream */
    glm::mat4x4 view = glm::lookAt(sourcePos, targetPos, glm::normalize(sourcePos));
    glm::mat4x4 model = glm::inverse(view) * scale;

    /* Send color */
    graphics->sendColorUniform(glm::vec4(m_color, 1.0));

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        if(m_particles[i])
        {
            float distance;

            /* Adjust distance based on relative size */
            if(target->getTransferRate(source) < source->getTransferRate(target))
            {
                distance = m_particles[i]->pos.z + 1;
            }
            else
            {
                distance = glm::abs(m_particles[i]->pos.z);
            }

            /* Particle expire by position */
            if(distance >= 1)
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

            /* Set particle velocity */
            float maxVel = glm::max((MAX_VEL / (totalDistance)) * (1 - totalDistance / maxDistance), MIN_VEL);
            float diff = (source->getTransferRate(target) - target->getTransferRate(source)) / totalDistance * (1 - totalDistance / maxDistance);
            float transVel = glm::clamp(diff * VEL_SCALE, -maxVel, maxVel);

            m_particles[i]->vel.z += transVel * 0.1;
            m_particles[i]->vel.z = glm::clamp(-maxVel, m_particles[i]->vel.z, maxVel);

            // Tick and draw particle
            m_particles[i]->tick(1.0 / 60.0);
            m_particles[i]->draw(graphics, look, model, m_particleSize);
        }
    }
}
