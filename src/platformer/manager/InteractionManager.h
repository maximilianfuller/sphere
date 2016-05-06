#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include "engine/manager/Manager.h"

class Entity;
class GameEntity;
class World;
class ParticleStreamSystem;

const int MAX_STREAMS = 5;

class InteractionManager : public Manager
{
public:
    InteractionManager(World *world, QList<Entity *> &entities);
    ~InteractionManager();

    void connect(GameEntity *e1, GameEntity *e2,
                 QList<std::pair<GameEntity *, GameEntity *> > &connections);

    void onTick(float seconds);
    void drawParticles(Graphics *graphics);

private:
    QList<ParticleStreamSystem *> m_streams;
};

#endif // INTERACTIONMANAGER_H
