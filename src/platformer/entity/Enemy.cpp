#include "Enemy.h"

#include "engine/world/World.h"
#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

Enemy::Enemy(World *world, float power, glm::vec3 color,
             glm::vec3 pos,
             float speed, glm::vec3 vel, glm::vec3 acc,
             glm::vec3 goal, float friction) :
    GameEntity(world, power, color, pos, speed, vel, acc, goal, friction)
{
}

Enemy::~Enemy()
{
}

void Enemy::idle()
{

    m_goal = glm::vec3();
}

void Enemy::updateGoalVelocity()
{
    glm::vec3 up = glm::normalize(m_pos);

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
            diff = diff - glm::dot(diff, up) * up;

            if(glm::length2(diff) > 0)
            {
                m_goal = glm::normalize(diff);
            }
        }
    }
    /* Approach weakest enemy */
    else if(m_delta >= 0)
    {
        GameEntity *minEnemy = NULL;
        float minDist = -1;

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

        if(minEnemy)
        {
            glm::vec3 diff = minEnemy->getPosition() - m_pos;
            diff = diff - glm::dot(diff, up) * up;
            diff = 0.9f * diff;

            if(glm::length2(diff) == 0)
            {
                diff = glm::normalize(glm::vec3(0.1, 0.1, 0.1));
            }

            m_goal = glm::normalize(diff);
        }
    }
    /* Random direction */
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
