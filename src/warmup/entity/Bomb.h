#ifndef BOMB_H
#define BOMB_H

#include "engine/entity/BackgroundEntity.h"
#include "warmup/entity/WarmupEntity.h"

class World;
class Floor;
class Player;

class Bomb : public BackgroundEntity, public WarmupEntity
{
public:
    Bomb(World *world, glm::vec3 pos = glm::vec3(0, 0, 0),
         float height = 0.2);
    ~Bomb();

    bool getExploding();

    /* Update methdods on tick */
    void updateShape();
    void updateBoundingShape();

    /* Game loop */
    void onIntersect(Entity *ent, glm::vec3 mtv);
    void onIntersect(Floor *floor, glm::vec3 mtv);
    void onIntersect(Player *player, glm::vec3 mtv);
    void onIntersect(Zombie *zombie, glm::vec3 mtv);

    void onTick(float seconds);

private:
    float m_height;
    float m_scale;

    bool m_exploding;
};

#endif // BOMB_H
