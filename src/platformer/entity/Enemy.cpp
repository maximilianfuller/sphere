#include "Enemy.h"

#include "engine/world/World.h"
#include "engine/light/PointLight.h"
#include "engine/particle/ParticleStreamSystem.h"

Enemy::Enemy(World *world, float power, glm::vec3 color,
             glm::vec3 pos, glm::vec3 dims,
             float speed, glm::vec3 vel, glm::vec3 acc,
             glm::vec3 goal, float friction) :
    m_follower(NULL),
    GameEntity(world, power, color, pos, dims, speed, vel, acc, goal, friction)
{
}

Enemy::~Enemy()
{
}

GameEntity *Enemy::getFollower()
{
    return m_follower;
}

void Enemy::setFollower(GameEntity *follower)
{
    m_follower = follower;
}

void Enemy::tryConnect(GameEntity *entity)
{
    float radius = m_light->getRadius();

    if(glm::length2(m_pos - entity->getPosition()) < radius * radius)
    {
        connect(entity);
        setTarget(entity);
    }
}

void Enemy::onConnected(GameEntity *entity)
{
    if(m_follower)
    {
        float dist = glm::length2(m_pos - m_follower->getPosition());

        if(glm::length2(m_pos - entity->getPosition()) < dist)
        {
            setFollower(entity);
        }
    }
    else
    {
        setFollower(entity);
    }
}

void Enemy::updateGoalVelocity()
{
    /* Update enemy */
    float rate = getTransferRate();

    if(m_target)
    {
        float targetRate = m_target->getTransferRate();

        glm::vec3 targetPos = m_target->getPosition();
        glm::vec3 diff = glm::vec3(targetPos.x - m_pos.x, 0, targetPos.z - m_pos.z);

        if(glm::length2(diff) > 0)
        {
            m_goal = glm::normalize(diff);
        }
    }

    if(m_follower)
    {
        float followerRate = m_follower->getTransferRate();

        glm::vec3 followerPos = m_follower->getPosition();
        glm::vec3 diff = glm::vec3(m_pos.x - followerPos.x, 0, m_pos.z - followerPos.z);

        if(glm::length2(diff) > 0)
        {
            m_goal = glm::normalize(diff);
        }
    }

    if(!m_target && !m_follower)
    {
        m_goal = glm::vec3(0);
    }
}

void Enemy::onTick(float seconds)
{
    GameEntity::onTick(seconds);

    /* Destroy enemy */
    if(m_power <= 0)
    {
        std::cout << "removed" << std::endl;
        std::cout << this << std::endl;
        m_world->removeEntity(this);
        return;
    }

    m_follower = NULL;
}
