#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <engine/manager/Manager.h>
#include <util/CommonIncludes.h>

class Player;
class GameWorld;

class EntityManager : public Manager
{
public:
    EntityManager(GameWorld *world, QList<Entity *> &entities, Player  *p);
    virtual void onTick(float seconds);
    void spawnEnemy(int level);
    void setPlayer(Player *player);

private:
    const float SPAWN_RADIUS = 60.f;
    const float NO_SPAWN_RADIUS = 30.f;
    const float MAX_ENEMIES = 15;
    const glm::vec3 START_LOC = glm::normalize(glm::vec3(1.f, 1.f, 1.f));
    const int NUM_LEVELS = 6;
    const float ENTITY_SPREAD = 2.1f; //how far each band of enemies continues past its "level boundary"
    const float SPAWN_RATE_COEFF = 1.5f;
    const float POWER_COEFF = .001;

    Player *m_player;
    float getEntitySpawnProbability(int level);
    glm::vec3 getColor(int level);
    float getPower(int level);
    float getSpeed(int level);
    glm::vec3 getRandomSpawnLoc(float spawnHeight);
    float getSpawnRadius();
    float getNoSpawnRadius();
};

#endif // ENTITYMANAGER_H
