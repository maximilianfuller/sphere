#ifndef BOUNDINGPLANE_H
#define BOUNDINGPLANE_H

#include "engine/intersect/BoundingShape.h"

class BoundingPlane : public BoundingShape
{
public:
    BoundingPlane(float level);
    ~BoundingPlane();

    ShapeType getShapeType() const;

    float getLevel();
    void setLevel(float level);

private:
    float m_level;
};

#endif // BOUNDINGPLANE_H
