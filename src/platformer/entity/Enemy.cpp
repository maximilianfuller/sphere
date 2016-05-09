#include "Enemy.h"

#include "engine/world/World.h"
#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

Enemy::Enemy(World *world, float power, glm::vec3 color,
             glm::vec3 pos, glm::vec3 dims,
             float speed, glm::vec3 vel, glm::vec3 acc,
             glm::vec3 goal, float friction) :
    GameEntity(world, power, color, pos, dims, speed, vel, acc, goal, friction)
{
}

Enemy::~Enemy()
{
}

void Enemy::idle()
{
}

void Enemy::updateGoalVelocity()
{
    /* Run from strongest enemy */
    if(m_delta < 0)
    {
        GameEntity *maxEnemy = NULL;
        float maxTransfer = 0;

        foreach(GameEntity *target, m_targets)
        {
            float transfer;

            if((transfer = target->getTransferRate(this)) > maxTransfer)
            {
                maxTransfer = transfer;
                maxEnemy = target;
            }
        }

        if(maxEnemy)
        {
            glm::vec3 diff = m_pos - maxEnemy->getPosition();

            if(glm::length2(diff) > 0)

            {
                m_goal = glm::normalize(diff);
            }
        }
    }
    /* Approach weakest enemy */
    else if(m_delta > 0)
    {
        GameEntity *minEnemy = NULL;
        float minTransfer = -1;

        foreach(GameEntity *target, m_targets)
        {
            float transfer;

            if(minTransfer < 0 || (transfer = target->getTransferRate(this)) < minTransfer)
            {
                minTransfer = transfer;
                minEnemy = target;
            }
        }

        if(minEnemy)
        {
            glm::vec3 diff = minEnemy->getPosition() - m_pos;

            if(glm::length2(diff) > 0)

            {
                m_goal = glm::normalize(diff);
            }
        }
    }
    /* Random direction */
    else
    {
        idle();
    }
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
