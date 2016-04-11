#ifndef LIGHT_H
#define LIGHT_H

#include "util/CommonIncludes.h"

class Graphics;

class Light
{
public:
    Light(glm::vec3 pos = glm::vec3(0, 0, 0),
          glm::vec3 att = glm::vec3(1, 0, 0),
          glm::vec3 intensity = glm::vec3(1, 1, 1));

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getAttenuation();
    void setAttenuation(glm::vec3 att);

    glm::vec3 getIntensity();
    void setIntensity(glm::vec3 intensity);

    virtual void draw(Graphics *graphics);

private:
    glm::mat4x4 m_model;
    glm::vec3 m_pos;
    glm::vec3 m_att;
    glm::vec3 m_int;
};

#endif // LIGHT_H
