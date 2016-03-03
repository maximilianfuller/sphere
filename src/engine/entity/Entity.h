#ifndef ENTITY_H
#define ENTITY_H

#include "util/CommonIncludes.h"

namespace Graphics {
class Controller;
}
class World;
class BoundingShape;
class Shape;

class Entity
{
public:
    Entity(World *world, glm::vec3 pos = glm::vec3(0, 0, 0),
           glm::vec3 dims = glm::vec3(1, 1, 1));
    virtual ~Entity();

    BoundingShape *getBoundingShape() const;

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    glm::vec3 getDimensions();
    void setDimensions(glm::vec3 dims);

    virtual void updateShape();
    virtual void updateBoundingShape();

    virtual bool intersect(Entity *ent);
    virtual void onIntersect(Entity *ent, glm::vec3 mtv);
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    World *m_world;
    BoundingShape *m_boundingShape;
    Shape *m_shape;

    glm::vec3 m_pos;
    glm::vec3 m_dims;
};

#endif // ENTITY_H
