#include "CylinderCollisionManager.h"

#include "engine/intersect/BoundingCylinder.h"
#include "engine/entity/ActiveEntity.h"
#include "engine/entity/BackgroundEntity.h"

CylinderCollisionManager::CylinderCollisionManager(QList<ActiveEntity *> &activeEnts,
                                                   QList<BackgroundEntity *> &backgroundEnts) :
    CollisionManager(activeEnts, backgroundEnts)
{
}

void CylinderCollisionManager::intersect(Entity *e1, Entity *e2)
{
    BoundingCylinder *c1 = dynamic_cast<BoundingCylinder *>(e1->getBoundingShape());
    BoundingCylinder *c2 = dynamic_cast<BoundingCylinder *>(e2->getBoundingShape());

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
    int numActiveEntities = m_activeEntities.size();

    /* Intersect active entities with one another */
    for(int i = 0; i < numActiveEntities; i++)
    {
        for(int j = i + 1; j < numActiveEntities; j++)
        {
            intersect(m_activeEntities[i], m_activeEntities[j]);
        }
    }

    int numBackgroundEntities = m_backgroundEntities.size();

    /* Intersect active entities with background entities */
    for(int i = 0; i < numActiveEntities; i++)
    {
        for(int j = 0; j < numBackgroundEntities; j++)
        {
            intersect(m_activeEntities[i], m_backgroundEntities[j]);
        }
    }
}
