#include "warmup/entity/Zombie.h"

#include "engine/world/World.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

#include "warmup/world/GameWorld.h"

#include "warmup/entity/Floor.h"
#include "warmup/entity/Player.h"
#include "warmup/entity/Bomb.h"

Zombie::Zombie(World *world, glm::vec3 pos, float height) :
    m_height(height),
    m_dead(false),
    m_untilDead(30),
    ActiveEntity(world, 3, pos),
    WarmupEntity(world),
    Entity(world)
{
    m_pos = pos;
    m_shape = new Cylinder(glm::vec3(0.5, 0, 0));
    m_boundingShape = new BoundingCylinder(m_pos, 0.5, m_height);

    updateShape();
    updateBoundingShape();
}

Zombie::~Zombie()
{
}

float Zombie::getHeight()
{
    return m_height;
}

void Zombie::updateFriction()
{
    return;
}

void Zombie::updateGoalVelocity()
{
    Player *player = dynamic_cast<GameWorld *>(m_world)->getPlayer();
    glm::vec3 diff = glm::vec3(player->getPosition().x - m_pos.x, 0,
                               player->getPosition().z - m_pos.z);

    if(glm::length(diff) > 0)
        m_goal = glm::normalize(diff);
}

void Zombie::updateAcceleration()
{
    if(!m_grounded)
        return;

    glm::vec3 diff = m_goal - m_vel;
    diff.x = m_friction * diff.x;
    diff.z = m_friction * diff.z;

    m_acc.x = diff.x;
    m_acc.z = diff.z;
}

void Zombie::updateShape()
{
    glm::vec3 pos = glm::vec3(m_pos.x, m_pos.y + m_height / 2, m_pos.z);
    glm::vec3 scale = glm::vec3(1, m_height, 1);

    glm::mat4x4 model = glm::mat4x4();
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);

    m_shape->setModelMatrix(model);
}

void Zombie::updateBoundingShape()
{
    BoundingCylinder *cyl = dynamic_cast<BoundingCylinder *>(m_boundingShape);
    cyl->setPosition(m_pos);
}

void Zombie::onIntersect(Entity *ent, glm::vec3 mtv)
{
    dynamic_cast<WarmupEntity *>(ent)->onIntersect(this, mtv);
}

void Zombie::onIntersect(Floor *floor, glm::vec3 mtv)
{
    /* Reset velocity */
    m_pos.y = 0;
    m_vel.y = 0;

    /* Set grounded flag */
    m_grounded = true;

    updateShape();
    updateBoundingShape();
}

void Zombie::onIntersect(Player *player, glm::vec3 mtv)
{
    updateShape();
    updateBoundingShape();
}

void Zombie::onIntersect(Zombie *zombie, glm::vec3 mtv)
{
    updateShape();
    updateBoundingShape();
}

void Zombie::onIntersect(Bomb *bomb, glm::vec3 mtv)
{
    m_vel += -3.5f * glm::normalize(mtv);
    m_vel.y += 2.f;

    m_dead = true;
    m_grounded = false;
}

void Zombie::onTick(float seconds)
{
    GameWorld *world = dynamic_cast<GameWorld *>(m_world);

    if(m_dead)
    {
        m_untilDead--;
    }

    if(m_untilDead <= 0)
    {
        world->removeActiveEntity(this);
        world->removeZombie();
        return;
    }

    ActiveEntity::onTick(seconds);
}
