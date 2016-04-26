#ifndef GEOMETRICMANAGER_H
#define GEOMETRICMANAGER_H

#include "engine/manager/Manager.h"
#include "util/CommonIncludes.h"

class Graphics;
class Entity;
class Ray;
class Triangle;
class TriangleData;
class Ellipsoid;
class NavMesh;
struct CollisionData;

const float EPS = 0.001;
const float SLIDE_BOUND = glm::cos(M_PI / 4.0);

class GeometricManager : public Manager
{
public:
    GeometricManager(QList<Triangle *> &triangles, QList<Entity *> &entities,
                     Graphics *graphics);
    ~GeometricManager();

    /* Raycasting */
    Triangle *getTriangleRay(QList<Triangle *> &triangles, Ray ray, CollisionData &data);
    Triangle *getTriangleBelow(QList<Triangle *> &triangles, glm::vec3 pos, CollisionData &data);

    /* Game loop */
    void onTick(float seconds);

    /* Navigation Mesh */
    NavMesh *navMesh;

private:
    /* Intersection calculation */
    bool intersectTriangles(QList<Triangle *> &ts, glm::vec3 startPos, glm::vec3 endPos,
                            glm::vec3 dims, CollisionData &data, Triangle *&tri);

    bool intersectTriangle(const Triangle &triangle, glm::vec3 startPos, glm::vec3 endPos,
                           CollisionData &data);

    /* Utility functions */
    bool intersectEnvironment(Entity *ent, glm::vec3 startPos, glm::vec3 endPos,
                              glm::vec3 &move, CollisionData &data);

    /* Game loop */
    void moveEntity(Entity *ent, float seconds);

    QList<Triangle *> &m_env;
};

#endif // GEOMETRICMANAGER_H
