#ifndef PARTICLETUBE_H
#define PARTICLETUBE_H

#include "util/CommonIncludes.h"

#include "engine/particle/ParticleSystem.h"

#include <QString>

class ParticleTube : public ParticleSystem
{
public:
    ParticleTube(QString textureKey,
                 glm::vec3 source, glm::vec3 target, glm::vec3 color,
                 float radius, float particleSize = 1);

    void setColor(glm::vec3 color);

    /* Create particles */
    void start();
    void stop();
    bool getStarted();

    void createParticle();

    void draw(Graphics *graphics, glm::mat4x4 look);

private:
    glm::vec3 m_source;
    glm::vec3 m_target;
    glm::vec3 m_color;

    float m_radius;
    float m_particleSize;

    bool m_started;
    int m_startTimer;

    int m_particleTimer;
    int m_particleTimeout;
};

#endif // PARTICLETUBE_H
