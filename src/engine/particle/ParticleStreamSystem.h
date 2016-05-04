#ifndef PARTICLESTREAMSYSTEM_H
#define PARTICLESTREAMSYSTEM_H


#include "util/CommonIncludes.h"
#include "engine/particle/ParticleSystem.h"

#include <QString>

class ParticleStreamSystem : public ParticleSystem
{
public:
    ParticleStreamSystem(QString textureKey,
                         glm::vec3 source, glm::vec3 target, glm::vec3 color,
                         float sourceRadius, float expireRadius,
                         float startVel);

    void setSource(glm::vec3 source);
    void setTarget(glm::vec3 target);
    void setColor(glm::vec3 color);
    void setSourceRadius(float radius);

    void start();
    void stop();
    bool getActivated();

    void createParticle();

    void draw(Graphics *graphics, glm::mat4x4 model);

private:
    glm::vec3 m_source;
    glm::vec3 m_target;
    glm::vec3 m_color;

    float m_sourceRadius;
    float m_expireRadius;

    float m_startVel;

    int m_stopTimer;
    bool m_activated;
};

#endif // PARTICLESTREAMSYSTEM_H
