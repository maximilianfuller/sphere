#include "CollisionManager.h"

#include "engine/entity/Entity.h"
#include "engine/planet/planetmanager.h"

#include "platformer/world/GameWorld.h"
#include "platformer/entity/GameEntity.h"

CollisionManager::CollisionManager(World *world, QList<Entity *> &entities) :
    Manager(world, entities)
{
}

void CollisionManager::onTick(float seconds)
{
    GameWorld *world = dynamic_cast<GameWorld *>(m_world);

    foreach(Entity *entity, m_entities)
    {
        GameEntity *ent = dynamic_cast<GameEntity *>(entity);

        float noise = world->getTerrainHeight(ent->getPosition());

        if(glm::length(ent->getPosition()) - ent->getRadius() * 0.25 < noise)
        {
            ent->setPosition(glm::normalize(ent->getPosition())
                             * (noise + ent->getRadius() * 0.25f));
            ent->setGrounded(true);
        }
        else
        {
            ent->setGrounded(false);
        }

        ent->onTick(seconds);
    }
}
