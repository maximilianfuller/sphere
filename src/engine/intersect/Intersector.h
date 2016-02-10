#ifndef INTERSECTOR_H
#define INTERSECTOR_H

#include "util/CommonIncludes.h"

class Entity;
class BoundingShape;

class BoundingPlane;
class BoundingCylinder;

namespace Intersector
{

void intersect(Entity *e1, Entity *e2);

bool hasIntersection(BoundingShape *s1, BoundingShape *s2, glm::vec3 &mtv1, glm::vec3 &mtv2);
bool hasIntersection(BoundingPlane *p, BoundingCylinder *c, glm::vec3 &mtv1, glm::vec3 &mtv2);
bool hasIntersection(BoundingCylinder *p, BoundingCylinder *c, glm::vec3 &mtv1, glm::vec3 &mtv2);

};

#endif // INTERSECTOR_H
