#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H

enum ShapeType {
    PlaneType,
    CylinderType
};

class BoundingShape
{
public:
    BoundingShape();
    virtual ~BoundingShape();

    virtual ShapeType getShapeType() const = 0;
};

#endif // BOUNDINGSHAPE_H
