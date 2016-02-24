#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "engine/entity/ActiveEntity.h"
#include "warmup/entity/WarmupEntity.h"

class World;
class Floor;
class Player;

class Zombie : public ActiveEntity, public WarmupEntity
{
public:
    Zombie(World *world, glm::vec3 pos = glm::vec3(0, 0, 0),
           float height = 1.0);
    ~Zombie();

    float getHeight();

    /* Update methods on tick */
    void updateFriction();
    void updateGoalVelocity();
    void updateAcceleration();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);
    void onIntersect(Floor *floor, glm::vec3 mtv);
    void onIntersect(Player *player, glm::vec3 mtv);
    void onIntersect(Zombie *zombie, glm::vec3 mtv);
    void onIntersect(Bomb *bomb, glm::vec3 mtv);

    void onTick(float seconds);

private:
    float m_height;

    int m_untilDead;
    bool m_dead;
};

#endif // ZOMBIE_H
