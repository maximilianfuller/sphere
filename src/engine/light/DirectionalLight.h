#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class Graphics;

class DirectionalLight : public Light
{
public:
    DirectionalLight(glm::vec3 dir = glm::vec3(1, 1, 1),
                     glm::vec3 intensity = glm::vec3(1, 1, 1),
                     int lightId = 0);

    void draw(Graphics *graphics);

private:
    glm::vec3 m_dir;
};

#endif // DIRECTIONALLIGHT_H
