#ifndef LIGHT_H
#define LIGHT_H

#include "util/CommonIncludes.h"

class Graphics;

static int numLights = 0;

class Light
{
public:
    Light(glm::vec3 intensity = glm::vec3(1, 1, 1));

    glm::vec3 getIntensity();
    void setIntensity(glm::vec3 intensity);

    virtual void draw(Graphics *graphics);

protected:
    glm::vec3 m_int;

    int m_id;
};

#endif // LIGHT_H
