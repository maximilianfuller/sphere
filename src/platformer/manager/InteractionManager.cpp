#include "InteractionManager.h"

#include "engine/entity/Entity.h"
#include "platformer/entity/GameEntity.h"

InteractionManager::InteractionManager(QList<Entity *> &entities) :
    Manager(entities)
{
}

void InteractionManager::onTick(float seconds)
{
    foreach(Entity *entity, m_entities)
    {
        GameEntity *ent = dynamic_cast<GameEntity *>(entity);
        ent->setConnected(false);
    }

    for(int i = 0; i < m_entities.length(); i++)
    {
        GameEntity *e1 = dynamic_cast<GameEntity *>(m_entities[i]);

        for(int j = i + 1; j < m_entities.length(); j++)
        {
            GameEntity *e2 = dynamic_cast<GameEntity *>(m_entities[j]);

            e1->tryConnect(e2);
            e2->tryConnect(e1);
        }
    }
}
