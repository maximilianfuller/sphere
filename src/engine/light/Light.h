#ifndef LIGHT_H
#define LIGHT_H

#include "util/CommonIncludes.h"

namespace Graphics
{
class Controller;
}

class Light
{
public:
    Light();
    virtual ~Light();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 &pos);

    glm::vec3 getColor();
    void setColor(glm::vec3 &color);

    virtual void draw(Graphics::Controller *graphics) = 0;

protected:
    glm::vec3 m_position;
    glm::vec3 m_color;
};

#endif // LIGHT_H
