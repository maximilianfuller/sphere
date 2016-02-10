#ifndef ENTITY_H
#define ENTITY_H

#include "util/CommonIncludes.h"

namespace Graphics {
class Controller;
}
class BoundingShape;
class Shape;

enum EntityType {
    BackgroundType,
    ActiveType
};

class Entity
{
public:
    Entity(glm::vec3 pos = glm::vec3(0, 0, 0));
    virtual ~Entity();

    BoundingShape *getBoundingShape() const;
    virtual EntityType getEntityType() const = 0;

    virtual void onIntersect(Entity *ent, glm::vec3 mtv);
    virtual void onTick(float seconds) = 0;
    virtual void onDraw(Graphics::Controller *graphics);

protected:
    BoundingShape *m_boundingShape;
    Shape *m_shape;

    glm::vec3 m_pos;
};

#endif // ENTITY_H
