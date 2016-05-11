#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
#include "util/CommonIncludes.h"

class Graphics;

const float MIN_INTENSITY = 1 / 1000.f;

class PointLight : public Light
{
public:
    PointLight(glm::vec3 pos = glm::vec3(0, 0, 0),
               glm::vec3 intensity = glm::vec3(1, 1, 1),
               glm::vec3 att = glm::vec3(0, 0, 1.0));

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getAttenuation();
    void setAttenuation(glm::vec3 att);

    glm::vec3 getLightColor();

    float getRadius();
    void setRadius(float radius);

    void draw(Graphics *graphics);

private:
    glm::vec3 m_pos;
    glm::vec3 m_att;

    float m_radius;
};

#endif // POINTLIGHT_H
