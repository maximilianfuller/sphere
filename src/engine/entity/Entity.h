#ifndef ENTITY_H
#define ENTITY_H

namespace Graphics {
class Controller;
}
class BoundingShape;
class Shape;

class Entity
{
public:
    Entity();
    virtual ~Entity();

    BoundingShape *getBoundingShape() const;
    virtual unsigned int getEntityType() = 0;

    virtual bool hasIntersection(Entity *ent);
    virtual void intersect(unsigned int e) = 0;
    virtual void tick(float seconds) = 0;
    virtual void draw(Graphics::Controller *graphics);

protected:
    BoundingShape *m_boundingShape;
    Shape *m_shape;
};

#endif // ENTITY_H
