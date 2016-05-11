#ifndef PARTICLESTREAMSYSTEM_H
#define PARTICLESTREAMSYSTEM_H


#include "util/CommonIncludes.h"

#include "engine/particle/ParticleSystem.h"

#include <QString>

class Entity;

const float VEL_SCALE = 100.f;
const float MAX_VEL = 0.01f;
const float MIN_VEL = 0.003f;

class ParticleStreamSystem : public ParticleSystem
{
public:
    ParticleStreamSystem(QString textureKey,
                         Entity *source, Entity *target, glm::vec3 color,
                         float particleSize = 1);

    /* Access attributes */
    Entity *getSource();
    void setSource(Entity *ent);

    Entity *getTarget();
    void setTarget(Entity *ent);

    void setColor(glm::vec3 color);

    /* Create particles */
    void start();
    void stop();
    bool getStarted();

    void createParticle();

    void draw(Graphics *graphics, glm::mat4x4 look);

private:
    Entity *m_source;
    Entity *m_target;
    glm::vec3 m_color;

    float m_particleSize;

    bool m_started;
    int m_startTimer;

    int m_particleTimer;
    int m_particleTimeout;
};

#endif // PARTICLESTREAMSYSTEM_H
