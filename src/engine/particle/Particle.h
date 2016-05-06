#ifndef PARTICLE_H
#define PARTICLE_H

#include "util/CommonIncludes.h"
#include <QString>

class Graphics;

const int MAX_AGE = 30;

class Particle
{
public:
    Particle(glm::vec3 pos = glm::vec3(0, 0, 0),
             glm::vec3 vel = glm::vec3(1, 1, 1),
             float noise1 = 1.0, float noise2 = 1.0,
             QString textureKey = QString(""));

    virtual void tick(float seconds);
    virtual void draw(Graphics *graphics, glm::mat4x4 look, glm::mat4x4 model);

    glm::vec3 pos;
    glm::vec3 vel;

    float u, v;
    float age;

    QString textureKey;
};

#endif // PARTICLE_H
