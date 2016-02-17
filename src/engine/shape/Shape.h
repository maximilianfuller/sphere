#ifndef SHAPE_H
#define SHAPE_H

#include "util/CommonIncludes.h"
#include "engine/graphics/Controller.h"

namespace Graphics {
class Controller;
}


class Shape
{
public:
    Shape(glm::mat4x4 model = glm::mat4x4(),
          glm::vec3 color = glm::vec3(0.5, 0.5, 0.5));
    virtual ~Shape();

    void rotateAbsolute(glm::vec3 axis, float angle);
    void translateAbsolute(glm::vec3 move);

    void rotateRelative(glm::vec3 axis, float angle);
    void translateRelative(glm::vec3 move);

    glm::mat4x4 getModelMatrix();
    void setModelMatrix(glm::mat4x4 model);

    virtual void draw(Graphics::Controller *graphics);

protected:
    glm::mat4x4 m_model;
    glm::vec3 m_color;
};

#endif // SHAPE_H
