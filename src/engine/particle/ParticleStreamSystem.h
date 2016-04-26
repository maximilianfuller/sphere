#ifndef PARTICLESTREAMSYSTEM_H
#define PARTICLESTREAMSYSTEM_H


#include "util/CommonIncludes.h"
#include "engine/particle/ParticleSystem.h"

#include <QString>

class ParticleStreamSystem : public ParticleSystem
{
public:
    ParticleStreamSystem(QString textureKey,
                         glm::vec3 start, glm::vec3 target,
                         float startRadius, float expireRadius,
                         float startVel);

    void setStart(glm::vec3 start);
    void setTarget(glm::vec3 target);

    void start();
    void stop();
    bool getActivated();

    void createParticle();

    void draw(Graphics *graphics, glm::mat4x4 model);

private:
    glm::vec3 m_start;
    glm::vec3 m_target;

    float m_startRadius;
    float m_expireRadius;

    float m_startVel;

    int m_stopTimer;
    bool m_activated;
};

#endif // PARTICLESTREAMSYSTEM_H
