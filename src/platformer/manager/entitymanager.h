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

private:
    float SPAWN_RADIUS = .05f;
    float NO_SPAWN_RADIUS = 0.01f;
    float MAX_ENEMIES = 30;
    glm::vec3 START_LOC = glm::normalize(glm::vec3(1.f, 1.f, 1.f));
    int NUM_LEVELS = 6;
    float ENTITY_SPREAD = 3.f; //how far each band of enemies continues past its "level boundary"
    float SPAWN_RATE_COEFF = 0.5f;
    float POWER_COEFF = .001;

    Player *m_player;
    float getEntitySpawnProbability(int level);
    void spawnEnemy(int level);
    glm::vec3 getColor(int level);
    float getPower(int level);
    float getSpeed(int level);
    glm::vec3 getRandomSpawnLoc(float spawnHeight);



};

#endif // ENTITYMANAGER_H
