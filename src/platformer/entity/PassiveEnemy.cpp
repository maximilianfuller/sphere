#include "PassiveEnemy.h"


PassiveEnemy::PassiveEnemy(World *world, float power, glm::vec3 color,
                           glm::vec3 pos,
                           float speed, glm::vec3 vel, glm::vec3 acc,
                           glm::vec3 goal, float friction) :
    Enemy(world, power, color, pos, speed, vel, acc, goal, friction)
{
}

PassiveEnemy::~PassiveEnemy()
{
}

void PassiveEnemy::updateGoalVelocity()
{
    /* Find stronger enemy */
    GameEntity *maxEnemy = NULL;
    float maxTransfer = 0;

    foreach(GameEntity *target, m_targets)
    {
        float transfer;

        if((transfer = target->getTransferRate(this)) > maxTransfer
                && transfer > getTransferRate(this))
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
