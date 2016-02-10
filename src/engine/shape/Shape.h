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
    Shape(glm::mat4x4 model = glm::mat4x4());
    virtual ~Shape();

    glm::mat4x4 getModelMatrix();
    void setModelMatrix(glm::mat4x4 model);

    virtual void draw(Graphics::Controller *graphics);

protected:
    glm::mat4x4 m_model;
};

#endif // SHAPE_H
