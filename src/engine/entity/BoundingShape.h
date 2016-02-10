#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H


class BoundingShape
{
public:
    BoundingShape();
    virtual ~BoundingShape();

    virtual bool intersect(BoundingShape *shape) = 0;
};

#endif // BOUNDINGSHAPE_H
