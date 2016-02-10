#include "warmup/entity/Floor.h"

#include "warmup/shape/TiledQuad.h"

Floor::Floor()
{
    m_shape = new TiledQuad();
}

Floor::~Floor()
{
}

unsigned int Floor::getEntityType()
{
    return 1;
}

bool Floor::hasIntersection(Entity *ent)
{
    return false;
}

void Floor::intersect(unsigned int e)
{
}

void Floor::tick(float seconds)
{
}
