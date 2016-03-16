#include "warmup/entity/Bomb.h"

#include "engine/world/World.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

#include "warmup/entity/Floor.h"
#include "warmup/entity/Player.h"
#include "warmup/entity/Zombie.h"

Bomb::Bomb(World *world, glm::vec3 pos, float height) :
    m_height(height),
    m_scale(1.0),
    m_exploding(false),
    WarmupEntity(world),
    BackgroundEntity(world),
    Entity(world, pos)
{
    m_shape = new Cylinder(m_pos, m_dims, glm::vec4(0, 0.5, 0, 1.0));
    m_boundingShape = new BoundingCylinder(m_pos, m_dims);
}

Bomb::~Bomb()
{
}

bool Bomb::getExploding()
{
    return m_exploding;
}

void Bomb::explode()
{
    m_dims.x += 0.2;
    m_dims.y += 0.2;
    m_dims.z += 0.2;
}

void Bomb::updateBoundingShape()
{
    Entity::updateBoundingShape();
}

void Bomb::onIntersect(Entity *ent, glm::vec3 mtv)
{
    dynamic_cast<WarmupEntity *>(ent)->onIntersect(this, mtv);
}

void Bomb::onIntersect(Floor *floor, glm::vec3 mtv)
{
}

void Bomb::onIntersect(Player *player, glm::vec3 mtv)
{
    return;
}

void Bomb::onIntersect(Zombie *zombie, glm::vec3 mtv)
{
    m_exploding = true;
}

void Bomb::onTick(float seconds)
{
    if(m_exploding)
    {
        m_scale *= 1.1;
        explode();
    }

    if(m_scale > 5.0)
    {
        m_world->removeBackgroundEntity(this);
        return;
    }

    BackgroundEntity::onTick(seconds);
}
