#include "CollisionManager.h"

#include "engine/entity/Entity.h"

CollisionManager::CollisionManager(World *world, QList<Entity *> &entities) :
    Manager(world, entities)
{
}

/* TODO:
 * Set uniforms for each entity
 * Run the shader program for each entity
 * Get the output
 * Set the location of the player
 * Set the acceleration of the player
 */
void CollisionManager::onTick(float seconds)
{
    foreach(Entity *ent, m_entities)
    {
        ent->setAcceleration(glm::vec3(0, 0, 0));
        ent->onTick(seconds);
    }
}
