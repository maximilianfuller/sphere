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
    Entity(world, pos),
    BackgroundEntity(world),
    WarmupEntity(world)
{
    m_pos = pos;
    m_shape = new Cylinder(glm::vec3(0, 0.5, 0));
    m_boundingShape = new BoundingCylinder(m_pos, 0.5, m_height);

    updateShape();
    updateBoundingShape();
}

Bomb::~Bomb()
{
}

bool Bomb::getExploding()
{
    return m_exploding;
}

void Bomb::updateShape()
{
    glm::vec3 pos = glm::vec3(m_pos.x, m_pos.y + m_height / 2, m_pos.z);
    glm::vec3 scale = glm::vec3(1, m_height, 1);

    if(m_exploding)
    {
        scale.x *= m_scale;
        scale.y *= m_scale * 2;
        scale.z *= m_scale;
    }

    glm::mat4x4 model = glm::mat4x4();
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);

    m_shape->setModelMatrix(model);
}

void Bomb::updateBoundingShape()
{
    BoundingCylinder *cyl = dynamic_cast<BoundingCylinder *>(m_boundingShape);
    cyl->setPosition(m_pos);
    cyl->setHeight(m_height);
    cyl->setRadius(0.5);

    if(m_exploding)
    {
        cyl->setPosition(glm::vec3(m_pos.x, m_height * 1.5, m_pos.z));
        cyl->setHeight(m_height * m_scale * 2 * 1.5);
        cyl->setRadius(m_scale * 1.2);
    }
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
    std::cout << "here" << std::endl;
    m_exploding = true;
}

void Bomb::onTick(float seconds)
{
    if(m_exploding)
    {
        m_scale *= 1.2;
    }

    if(m_scale > 5.0)
    {
        m_world->removeBackgroundEntity(this);
        return;
    }

    updateShape();
    updateBoundingShape();
}
