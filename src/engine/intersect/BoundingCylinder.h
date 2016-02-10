#ifndef BOUNDINGCYLINDER_H
#define BOUNDINGCYLINDER_H

#include "engine/intersect/BoundingShape.h"
#include "util/CommonIncludes.h"

class BoundingCylinder : public BoundingShape
{
public:
    BoundingCylinder(glm::vec3 pos, float radius, float height);
    ~BoundingCylinder();

    ShapeType getShapeType() const;

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);

    float getRadius();
    void setRadius(float radius);

    float getHeight();
    void setHeight(float height);

private:
    glm::vec3 m_pos;
    float m_radius;
    float m_height;
};

#endif // BOUNDINGCYLINDER_H
