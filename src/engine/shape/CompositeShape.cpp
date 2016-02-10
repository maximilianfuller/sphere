#include "engine/shape/CompositeShape.h"

#include "engine/graphics/Controller.h"

CompositeShape::CompositeShape(glm::mat4x4 model) :
    Shape(model)
{
}

CompositeShape::~CompositeShape()
{
    QList<Shape *>::iterator s;

    for(s = m_children.begin(); s != m_children.end(); s++)
    {
        delete *s;
    }
}

Shape *CompositeShape::getChild(int index)
{
    return m_children[index];
}

void CompositeShape::addChild(Shape *child)
{
    m_children.append(child);
}

void CompositeShape::removeChild(Shape *child)
{
    QList<Shape *>::iterator s;
    int i = 0;

    for(s = m_children.begin(); s != m_children.end(); s++)
    {
        if(*s == child)
            break;

        i++;
    }

    m_children.removeAt(i);
}

void CompositeShape::draw(Graphics::Controller *graphics)
{
    Shape::draw(graphics);
}
