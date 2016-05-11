#include "entitymanager.h"
#include "engine/entity/Entity.h"
#include "platformer/entity/Player.h"
#include "platformer/world/GameWorld.h"
#include "platformer/entity/Enemy.h"

EntityManager::EntityManager(GameWorld *world, QList<Entity *> &entities, Player  *p) : Manager(world, entities) {
    m_player = p;
    srand(0);
}

void EntityManager::onTick(float seconds) {

    QList<Entity *> toRemove;

    //remove entities outside of range
    for(int i = 0; i < m_entities.length(); i++) {
        Entity *e = m_entities.value(i);
        if(e != m_player) {
            float f = glm::length(e->getPosition()-m_player->getPosition());
            if(glm::length(e->getPosition()-m_player->getPosition()) > SPAWN_RADIUS) {
               toRemove.append(e);
            }
        }
    }
    for(int i = 0; i < toRemove.length(); i++) {
        Entity *e = toRemove.value(i);
        m_world->removeEntity(e);
    }

    if(m_entities.length()-1 < MAX_ENEMIES) {
        for(int level = 1; level <= NUM_LEVELS; level++) {
            float dieRoll = rand()/(float)RAND_MAX;
            float prob = getEntitySpawnProbability(level)*seconds;
            if (dieRoll < prob) {
                spawnEnemy(level);
            }
        }
    }
}

void EntityManager::spawnEnemy(int level) {
    Enemy *e = new Enemy(m_world, getPower(level), getColor(level),getRandomSpawnLoc(.001f), getSpeed(level));
    m_world->addEntity(e);
}

glm::vec3 EntityManager::getColor(int level) {

    glm::vec3 color;

    switch(level) {
    case 1:
        color = glm::vec3(128,0,255);
        break;
    case 2:
        color = glm::vec3(0,0,255);
        break;
    case 3:
        color = glm::vec3(0,255,175);
        break;
    case 4:
        color = glm::vec3(0,255,0);
        break;
    case 5:
        color = glm::vec3(255,255,0);
        break;
    case 6:
        color = glm::vec3(255,0,0);
        break;
    default:
        color = glm::vec3(1,1,1);
    }
    return color/255.f;
}

float EntityManager::getPower(int level) {
    return glm::pow(8.f, level-1.f)*POWER_COEFF;
}

float EntityManager::getSpeed(int level) {
    return 0.0005f * glm::pow(2.f, level-1.f);
}

glm::vec3 EntityManager::getRandomSpawnLoc(float spawnHeight) {

    //get random value in unit circle
    float x, y;
    do {
        x = 2*(rand()/(float)RAND_MAX)-1.f;
        y = 2*(rand()/(float)RAND_MAX)-1.f;
    } while (x*x + y*y > 1.f && sqrt(x*x + y*y) < SPAWN_RADIUS/NO_SPAWN_RADIUS);

    //get perpindicular vector;
    glm::vec3 up = glm::normalize(m_player->getPosition());
    glm::vec3 perp = glm::cross(up, glm::vec3(1.f, 0.f, 0.f));
    if(glm::length(perp) == 0.f) {
        glm::cross(up, glm::vec3(0.f, 1.f, 0.f));
    }

    //get axis
    glm::vec3 xDir = glm::normalize(perp);
    glm::vec3 yDir = glm::normalize(glm::cross(perp, up));

    //get raw position and project onto terrain surface (+ spawnHeight)
    glm::vec3 pos =  m_player->getPosition() + xDir*x*SPAWN_RADIUS + yDir*y*SPAWN_RADIUS;
    float terrainHeight = dynamic_cast<GameWorld *>(m_world)->getTerrainHeight(pos);


    return (terrainHeight+spawnHeight)*glm::normalize(pos);
}

float EntityManager::getEntitySpawnProbability(int level) {
    float theta = glm::acos(glm::dot(START_LOC, glm::normalize(m_player->getPosition())));
    float areaLevel = (theta/(M_PI))*NUM_LEVELS;
    float distToAreaLevel = glm::abs(level - areaLevel);
    float prob = glm::max(ENTITY_SPREAD - distToAreaLevel, 0.f)*SPAWN_RATE_COEFF;
    return prob;

}

