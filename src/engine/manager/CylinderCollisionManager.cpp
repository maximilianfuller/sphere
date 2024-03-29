#include "CylinderCollisionManager.h"

#include "engine/shape/Cylinder.h"
#include "engine/entity/Entity.h"
#include "engine/world/World.h"

CylinderCollisionManager::CylinderCollisionManager(World *world, QList<Entity *> &entities) :
    Manager(world, entities)
{
}

void CylinderCollisionManager::intersect(Entity *e1, Entity *e2)
{
    Cylinder *c1 = dynamic_cast<Cylinder *>(e1->getShape());
    Cylinder *c2 = dynamic_cast<Cylinder *>(e2->getShape());

    glm::vec3 c1Pos = c1->getPosition();
    glm::vec3 c2Pos = c2->getPosition();
    glm::vec3 c1Dims = c1->getDimensions();
    glm::vec3 c2Dims = c2->getDimensions();

    glm::vec3 v = glm::vec3(c1Pos.x - c2Pos.x, 0, c1Pos.z - c2Pos.z);

    glm::vec3 mtv;
    glm::vec3 mtvRadial = (c1Dims.x / 2 + c2Dims.x / 2) * glm::normalize(v) - v;
    glm::vec3 mtvHeight = glm::vec3(0, glm::min(c1Pos.y + c1Dims.y - c2Pos.y,
                                                c2Pos.y + c2Dims.y - c1Pos.y),
                                    0);

    bool intersectRadial = glm::length2(v) < (c1Dims.x / 2 + c2Dims.x / 2)
            * (c1Dims.x / 2 + c2Dims.x / 2);
    bool intersectHeight = (c1Pos.y + c1Dims.y > c2Pos.y)
            && (c2Pos.y + c2Dims.y > c1Pos.y);

    if(glm::length2(mtvRadial) < glm::length2(mtvHeight))
    {
        mtv = mtvRadial;
    }
    else
    {
        mtv = mtvHeight;
    }

    if(intersectRadial && intersectHeight)
    {
        e1->setPosition(e1->getPosition() + mtv / 1.9f);
        e2->setPosition(e2->getPosition() - mtv / 1.9f);

        e1->onIntersect(e2, mtv);
        e2->onIntersect(e1, -mtv);
    }
}

void CylinderCollisionManager::onTick(float seconds)
{
    int numEnts = m_entities.size();

    /* Intersect entities with one another */
    for(int i = 0; i < numEnts; i++)
    {
        for(int j = i + 1; j < numEnts; j++)
        {
            intersect(m_entities[i], m_entities[j]);
        }
    }

    Manager::onTick(seconds);
}
