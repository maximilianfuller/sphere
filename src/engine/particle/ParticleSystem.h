#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "util/CommonIncludes.h"

#include <QString>

class Graphics;
class Particle;

const int MAX_PARTICLES = 500;

class ParticleSystem
{
public:
    ParticleSystem(QString textureKey);
    virtual ~ParticleSystem();

    void tick(float seconds);
    void draw(Graphics *graphics);

private:
    Particle* m_particles[MAX_PARTICLES];
    int m_particleIndex = 0;

    QString m_textureKey;
};


#endif // PARTICLESYSTEM_H
