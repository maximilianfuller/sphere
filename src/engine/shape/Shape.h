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
    Shape(glm::vec3 pos = glm::vec3(0, 0, 0),
          glm::vec3 dims = glm::vec3(1, 1, 1),
          glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1.0));
    Shape(glm::mat4x4 model,
          glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1.0));
    virtual ~Shape();

    void rotate(glm::mat4x4 model, glm::vec3 axis, float angle);
    void translate(glm::mat4x4 model, glm::vec3 move);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getDimensions();
    void setDimensions(glm::vec3 dims);

    glm::vec4 getColor();
    void setColor(glm::vec4 color);

    glm::mat4x4 getModelMatrix();
    void setModelMatrix(glm::mat4x4 model);

    virtual void draw(Graphics::Controller *graphics);

protected:
    glm::mat4x4 m_model;
    glm::vec3 m_pos;
    glm::vec3 m_dims;
    glm::vec4 m_color;
};

#endif // SHAPE_H
