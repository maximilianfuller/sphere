#include "warmup/entity/Floor.h"

#include "engine/intersect/BoundingPlane.h"

#include "warmup/shape/TiledQuad.h"

Floor::Floor()
{
    m_shape = new TiledQuad();
    m_boundingShape = new BoundingPlane(0);
}

Floor::~Floor()
{
}
