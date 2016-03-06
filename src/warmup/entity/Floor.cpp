#include "warmup/entity/Floor.h"

#include "engine/world/World.h"

#include "warmup/shape/TiledQuad.h"

Floor::Floor(World *world) :
    Entity(world),
    BackgroundEntity(world),
    WarmupEntity(world)
{
    m_shape = new TiledQuad();
}

Floor::~Floor()
{
}

void Floor::onIntersect(Entity *ent, glm::vec3 mtv)
{
    dynamic_cast<WarmupEntity *>(ent)->onIntersect(this, mtv);
}
