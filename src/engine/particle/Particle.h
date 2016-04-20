#ifndef PARTICLE_H
#define PARTICLE_H

#include "util/CommonIncludes.h"
#include <QString>

class Graphics;

class Particle
{
public:
    Particle(glm::vec3 pos = glm::vec3(0, 0, 0),
             glm::vec3 vel = glm::vec3(1, 1, 1),
             QString textureKey = QString(""));

    void setPos(glm::vec3 pos);
    void setVel(glm::vec3 vel);
    void setTextureKey(QString textureKey);

    float getAge();

    virtual void tick(float seconds);
    virtual void draw(Graphics *graphics);

private:
    glm::vec3 m_pos;
    glm::vec3 m_vel;
    float m_age;

    QString m_textureKey;
};

#endif // PARTICLE_H
