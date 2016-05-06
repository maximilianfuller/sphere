#include "InteractionManager.h"

#include "engine/entity/Entity.h"
#include "engine/world/World.h"
#include "engine/camera/Camera.h"
#include "engine/particle/ParticleStreamSystem.h"

#include "platformer/entity/GameEntity.h"

#include <QMutableListIterator>

InteractionManager::InteractionManager(World *world, QList<Entity *> &entities) :
    Manager(world, entities)
{
}

InteractionManager::~InteractionManager()
{
    foreach(ParticleStreamSystem *stream, m_streams)
    {
        delete(stream);
    }
}

void InteractionManager::connect(GameEntity *e1, GameEntity *e2,
                                 QList<std::pair<GameEntity *, GameEntity *> > &connections)
{
    float minDist = e1->getLightRadius() + e2->getLightRadius();

    if(glm::length2(e1->getPosition() - e2->getPosition()) < minDist * minDist)
    {
        if(!e1->hasTarget(e2))
        {
            ParticleStreamSystem *stream = new ParticleStreamSystem(
                        "particle", e1, e2,
                        glm::mix(e1->getLightColor(), e2->getLightColor(), 0.5),
                        7.f);

            m_streams.append(stream);

            e1->addTarget(e2);
            e2->addTarget(e1);
        }

        connections.append(std::pair<GameEntity *, GameEntity *>(e1, e2));
    }
}

void InteractionManager::onTick(float seconds)
{
    QList<std::pair<GameEntity *, GameEntity *> > connections;

    /* Create streams */
    for(int i = 0; i < m_entities.length(); i++)
    {
        GameEntity *e1 = dynamic_cast<GameEntity *>(m_entities[i]);

        for(int j = i + 1; j < m_entities.length(); j++)
        {
            GameEntity *e2 = dynamic_cast<GameEntity *>(m_entities[j]);
            connect(e1, e2, connections);
        }
    }

    /* Prune targets */
    foreach(Entity *entity, m_entities)
    {
        GameEntity *ent = dynamic_cast<GameEntity *>(entity);
        ent->clearTargets();
    }

    for(int i = 0; i < connections.length(); i++)
    {
        std::pair<GameEntity *, GameEntity *> c = connections[i];
        c.first->addTarget(c.second);
        c.second->addTarget(c.first);
    }

    /* Prune streams */
    QMutableListIterator<ParticleStreamSystem *> i(m_streams);

    while(i.hasNext())
    {
        ParticleStreamSystem *stream = i.next();

        if(!m_entities.contains(stream->getSource())
                || !m_entities.contains(stream->getTarget()))
        {
            delete(stream);
            i.remove();
            continue;
        }

        GameEntity *e1 = dynamic_cast<GameEntity *>(stream->getSource());
        GameEntity *e2 = dynamic_cast<GameEntity *>(stream->getTarget());

        if(!e1->hasTarget(e2))
        {
            delete(stream);
            i.remove();
            continue;
        }

        if(m_streams.length() < MAX_STREAMS && !stream->getStarted())
        {
            stream->start();
        }
    }
}

void InteractionManager::drawParticles(Graphics *graphics)
{
    foreach(ParticleStreamSystem *stream, m_streams)
    {
        Camera *camera = m_world->getCamera();
        stream->draw(graphics,
                     glm::mat4x4(glm::mat3x3(glm::inverse(camera->getView()))));
    }
}
