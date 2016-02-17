#include "warmup/entity/Floor.h"

#include "engine/world/World.h"
#include "engine/intersect/BoundingPlane.h"

#include "warmup/shape/TiledQuad.h"

Floor::Floor(World *world) :
    Entity(world),
    BackgroundEntity(world),
    WarmupEntity(world)
{
    m_shape = new TiledQuad();
    m_boundingShape = new BoundingPlane(0);
}

Floor::~Floor()
{
}

void Floor::onIntersect(Entity *ent, glm::vec3 mtv)
{
    dynamic_cast<WarmupEntity *>(ent)->onIntersect(this, mtv);
}
