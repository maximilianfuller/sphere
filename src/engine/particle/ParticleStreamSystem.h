#ifndef PARTICLESTREAMSYSTEM_H
#define PARTICLESTREAMSYSTEM_H


#include "util/CommonIncludes.h"

#include "engine/particle/ParticleSystem.h"

#include <QString>

class Entity;

class ParticleStreamSystem : public ParticleSystem
{
public:
    ParticleStreamSystem(QString textureKey,
                         Entity *source, Entity *target, glm::vec3 color,
                         float startVel);

    /* Access attributes */
    Entity *getSource();
    void setSource(Entity *ent);

    Entity *getTarget();
    void setTarget(Entity *ent);

    void setColor(glm::vec3 color);

    /* Create particles */
    bool start();

    void createParticle(bool start);

    void draw(Graphics *graphics, glm::mat4x4 look);

private:
    Entity *m_source;
    Entity *m_target;
    glm::vec3 m_color;

    bool m_started;
    int m_startTimer;

    float m_startVel;

    int m_particleTimer;
    int m_particleTimeout;
};

#endif // PARTICLESTREAMSYSTEM_H
