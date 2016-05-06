#ifndef RAY_H
#define RAY_H

#include "util/CommonIncludes.h"

struct CollisionData
{
    float t;
    glm::vec3 n;
};
class Triangle;

class Ray
{
public:
    Ray(glm::vec3 p, glm::vec3 d);

    glm::vec3 getPos();
    void setPos(glm::vec3 pos);

    glm::vec3 getDir();
    void setDir(glm::vec3 dir);

    bool intersectTriangle(const Triangle &triangle, CollisionData &data);
    bool intersectSphere(glm::vec3 center, float radius, CollisionData &data);
    bool intersectCylinder(glm::vec3 v1, glm::vec3 v2, CollisionData &data);
    bool quadMinSolution(float a, float b, float c, float &t);

protected:
    glm::vec3 m_pos, m_dir;
};

#endif // RAY_H
