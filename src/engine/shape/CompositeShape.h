#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include "engine/shape/Shape.h"

#include <QList>

namespace Graphics
{
class Controller;
}

class CompositeShape : public Shape
{
public:
    CompositeShape(glm::mat4x4 model = glm::mat4x4());
    virtual ~CompositeShape();

    // NOTE: duplicate shape pointers may not be added to the composite shape
    Shape *getChild(int index);
    void addChild(Shape *child);
    void removeChild(Shape *child);

    virtual void draw(Graphics::Controller *graphics);

protected:
    QList<Shape *> m_children;
};

#endif // COMPOSITESHAPE_H
