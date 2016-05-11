#include "Enemy.h"

#include "engine/world/World.h"
#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

#include <glm/gtx/rotate_vector.hpp>

Enemy::Enemy(World *world, float power, glm::vec3 color,
             glm::vec3 pos,
             float speed, glm::vec3 vel, glm::vec3 acc,
             glm::vec3 goal, float friction) :
    GameEntity(world, power, color, pos, speed, vel, acc, goal, friction * 0.5)
{
    float rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float rand3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    m_goal = glm::normalize(glm::vec3(rand1, rand2, rand3));
}

Enemy::~Enemy()
{
}

void Enemy::idle()
{
    glm::vec3 up = glm::normalize(m_pos);
    float yaw = (M_PI / 6) * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    m_goal = glm::rotate(m_goal, yaw, up);
}

void Enemy::updateGoalVelocity()
{
    glm::vec3 up = glm::normalize(m_pos);
    GameEntity *maxEnemy = NULL;
    GameEntity *minEnemy = NULL;

    /* Get closest larger */
    float minDist = -1;

    foreach(Entity *entity, m_world->getEntities())
    {
        GameEntity *target = dynamic_cast<GameEntity *>(entity);

        float range = (target->getLightRadius() + getLightRadius()) * 0.5f;
        float dist = glm::length(target->getPosition() - m_pos);

        if(dist < range)
        {
            float transfer = target->getTransferRate(this);

            if(minDist < 0 || dist < minDist && transfer > getTransferRate(target))
            {
                minDist = dist;
                maxEnemy = target;
            }
        }
    }

    /* Get closest smaller */
    minDist = -1;

    foreach(Entity *entity, m_world->getEntities())
    {
        GameEntity *target = dynamic_cast<GameEntity *>(entity);

        float range = (target->getLightRadius() + getLightRadius()) * 0.5f;
        float dist = glm::length(target->getPosition() - m_pos);

        if(dist < range)
        {
            float transfer = target->getTransferRate(this);

            if(minDist < 0 || dist < minDist && transfer < getTransferRate(target))
            {
                minDist = dist;
                minEnemy = target;
            }
        }
    }


    if(maxEnemy && m_delta < 0)
    {
        glm::vec3 diff = m_pos - maxEnemy->getPosition();
        diff = diff - glm::dot(diff, up) * up;

        if(glm::length2(diff) > 0)
        {
            m_goal = glm::normalize(diff);
        }
    }
    else if(minEnemy && m_delta >= 0)
    {
        glm::vec3 diff = minEnemy->getPosition() - m_pos;
        diff = diff - glm::dot(diff, up) * up;
        diff = diff - minEnemy->getRadius() * 3.f * diff;

        if(glm::length2(diff) != 0)
        {
            m_goal = glm::normalize(diff);
        }
    }
    else
    {
        idle();
    }

    m_goal = m_goal - glm::dot(m_goal, up) * up;
}

void Enemy::onTick(float seconds)
{
    GameEntity::onTick(seconds);

    /* Destroy enemy */
    if(m_power <= 0)
    {
        m_world->removeEntity(this);
        return;
    }
}
