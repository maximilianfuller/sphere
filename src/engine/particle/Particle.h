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

    virtual void tick(float seconds);
    virtual void draw(Graphics *graphics, glm::mat4x4 model);

    glm::vec3 pos;
    glm::vec3 vel;
    float age;

    QString textureKey;
};

#endif // PARTICLE_H
