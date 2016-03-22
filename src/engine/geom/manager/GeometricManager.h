#ifndef GEOMETRICMANAGER_H
#define GEOMETRICMANAGER_H

#include "engine/manager/Manager.h"
#include "util/CommonIncludes.h"

class Entity;
class Triangle;
class Ellipsoid;
namespace Graphics
{
class Controller;
}
struct CollisionData;

const float EPS = 0.001;
const float SLIDE_BOUND = glm::cos(M_PI / 4.0);

class GeometricManager : public Manager
{
public:
    GeometricManager(QList<Triangle *> &triangles, QList<Entity *> &entities);

    /* Intersection calculation */
    bool intersectTriangles(QList<Triangle *> &ts, glm::vec3 startPos, glm::vec3 endPos,
                            glm::vec3 dims, CollisionData &data);

    bool intersectTriangle(const Triangle &triangle, glm::vec3 p, glm::vec3 d,
                           CollisionData &data);

    /* Utility functions */
    bool intersectEnvironment(Entity *ent, glm::vec3 startPos, glm::vec3 endPos,
                              glm::vec3 &move, CollisionData &data);

    /* Game loop */
    void moveEntity(Entity *ent, float seconds);

    void onTick(float seconds);
    void onDraw(Graphics::Controller *graphics);

private:
    QList<Triangle *> &m_env;
};

#endif // GEOMETRICMANAGER_H
