#include "minecraft/entity/MinecraftEnemy.h"

#include "engine/graphics/Controller.h"
#include "engine/camera/Camera.h"
#include "engine/shape/Cylinder.h"
#include "engine/intersect/BoundingCylinder.h"

#include "engine/voxel/manager/VoxelManager.h"
#include "engine/voxel/block/Block.h"

#include "minecraft/manager/MinecraftManager.h"
#include "minecraft/entity/MinecraftPlayer.h"

/* TODO: fix groundedness */
MinecraftEnemy::MinecraftEnemy(MinecraftManager *manager, glm::vec3 pos) :
    m_jump(false),
    VoxelEntity(manager, 5.0),
    Entity(manager, pos, glm::vec3(0.8, 1, 0.8))
{
    /* Create shape and bounding shape */
    m_shape = new Cylinder();
    m_boundingShape = new BoundingCylinder(m_pos, m_dims);

    /* Update shape and bounding shape to correspond to player's dimentions */
    updateShape();
    updateBoundingShape();
}

MinecraftEnemy::~MinecraftEnemy()
{
}

void MinecraftEnemy::jump()
{
    m_grounded = false;
    m_vel.y = JUMP_SPEED;
}

void MinecraftEnemy::updateFriction()
{
    m_friction = m_grounded ? MU_GROUND : MU_AIR;
}

void MinecraftEnemy::updateGoalVelocity()
{
    glm::vec3 playerPos = dynamic_cast<VoxelManager *>(m_world)->getPlayer()->getPosition();
    glm::vec3 diff = glm::vec3(playerPos.x - m_pos.x, 0, playerPos.z - m_pos.z);

    if(glm::length(diff) > 0)
    {
        m_goal = glm::normalize(diff);
    }

    if(playerPos.y > m_pos.y && m_grounded)
    {
        m_jump = true;
    }
    else
    {
        m_jump = false;
    }
}

void MinecraftEnemy::updateAcceleration()
{
    glm::vec3 diff = m_goal - m_vel;
    diff.x = m_friction * diff.x;
    diff.z = m_friction * diff.z;

    m_acc.x = diff.x;
    m_acc.z = diff.z;
}

void MinecraftEnemy::onIntersect(Entity *ent, glm::vec3 mtv)
{
    dynamic_cast<VoxelEntity *>(ent)->onIntersect(this, mtv);
}

void MinecraftEnemy::onIntersect(MinecraftPlayer *ent, glm::vec3 mtv)
{
}

void MinecraftEnemy::onIntersect(MinecraftEnemy *ent, glm::vec3 mtv)
{
}


void MinecraftEnemy::onTick(float seconds)
{
    /* Jump */
    if(m_jump && m_grounded)
    {
        jump();
    }

    /* Call superclass method to update player */
    VoxelEntity::onTick(seconds);

    /* Remove if necessary */
    MinecraftManager *manager = dynamic_cast<MinecraftManager *>(m_world);

    if(!manager->getChunk(m_pos.x, m_pos.y, m_pos.z))
    {
        manager->removeActiveEntity(this);
    }
}
