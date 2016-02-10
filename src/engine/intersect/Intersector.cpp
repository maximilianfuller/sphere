#include "engine/intersect/Intersector.h"

#include "engine/entity/Entity.h"
#include "engine/entity/BackgroundEntity.h"
#include "engine/entity/ActiveEntity.h"
#include "engine/intersect/BoundingShape.h"
#include "engine/intersect/BoundingCylinder.h"
#include "engine/intersect/BoundingPlane.h"

void Intersector::intersect(Entity *e1, Entity *e2)
{
    if(e1->getEntityType() == BackgroundType && e2->getEntityType() == BackgroundType)
    {
        return;
    }

    glm::vec3 mtv1, mtv2;

    if(hasIntersection(e1->getBoundingShape(), e2->getBoundingShape(), mtv1, mtv2))
    {
        if(e1->getEntityType() == BackgroundType)
        {
            mtv2 = mtv2 - mtv1;
            mtv1 = glm::vec3(0, 0, 0);
        }
        else if(e2->getEntityType() == BackgroundType)
        {
            mtv1 = mtv1 - mtv2;
            mtv2 = glm::vec3(0, 0, 0);
        }

        e1->onIntersect(e1, mtv1);
        e2->onIntersect(e2, mtv2);
    }
}

bool Intersector::hasIntersection(BoundingShape *s1, BoundingShape *s2, glm::vec3 &mtv1, glm::vec3 &mtv2)
{
    if(s1->getShapeType() == PlaneType && s2->getShapeType() == CylinderType)
    {
        return hasIntersection(dynamic_cast<BoundingPlane *>(s1),
                               dynamic_cast<BoundingCylinder *>(s2), mtv1, mtv2);
    }
    else if(s1->getShapeType() == CylinderType && s2->getShapeType() == PlaneType)
    {
        return hasIntersection(dynamic_cast<BoundingPlane *>(s2),
                               dynamic_cast<BoundingCylinder *>(s1), mtv2, mtv1);
    }
    else if(s1->getShapeType() == CylinderType && s2->getShapeType() == CylinderType)
    {
        return hasIntersection(dynamic_cast<BoundingCylinder *>(s2),
                               dynamic_cast<BoundingCylinder *>(s1), mtv1, mtv2);
    }
    else
    {
        return false;
    }
}

bool Intersector::hasIntersection(BoundingPlane *p, BoundingCylinder *c, glm::vec3 &mtv1, glm::vec3 &mtv2)
{
    glm::vec3 mtv = glm::vec3(0, c->getPosition().y - p->getLevel(), 0);
    mtv1 = 0.5f * mtv;
    mtv2 = -0.5f * mtv;

    return mtv.y < 0;
}

bool Intersector::hasIntersection(BoundingCylinder *p, BoundingCylinder *c, glm::vec3 &mtv1, glm::vec3 &mtv2)
{
}
