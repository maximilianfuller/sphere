#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "util/CommonIncludes.h"

#include <QString>

class Graphics;
class Particle;

const int MAX_PARTICLES = 200;

class ParticleSystem
{
public:
    ParticleSystem(QString textureKey);
    virtual ~ParticleSystem();

    virtual void draw(Graphics *graphics, glm::mat4x4 model);

protected:
    Particle* m_particles[MAX_PARTICLES];
    int m_particleIndex;

    QString m_textureKey;
};


#endif // PARTICLESYSTEM_H
