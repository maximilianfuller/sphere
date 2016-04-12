#include "GeometricManager.h"

#include "engine/graphics/Graphics.h"

#include "engine/intersect/Ray.h"
#include "engine/intersect/Triangle.h"
#include "engine/shape/Ellipsoid.h"
#include "engine/entity/Entity.h"

#include "util/obj.h"
#include "engine/geom/nav/NavMesh.h"

/*
 * 2) Transform mouse position to environment ray (game world / player)
 * 3) Raycast nav mesh with ray
 * 4) Draw raycasted location in world (ellipsoid for drawing)
 * 5) Once raycasted target, create path
 * 6) Create list of ellipses for drawing on the fly (save path?)
 * 7) Draw them
 * 8) SSF
*/
GeometricManager::GeometricManager(QList<Triangle *> &triangles, QList<Entity *> &entities,
                                   Graphics *graphics) :
    m_env(triangles),
    navMesh(new NavMesh(triangles, graphics)),
    Manager(entities)
{
    CollisionData data;
    Triangle *start = getTriangleBelow(navMesh->triangles, glm::vec3(0, 2, 0), data);
    Triangle *end = getTriangleBelow(navMesh->triangles, glm::vec3(0, 10, 10), data);

    QList<glm::vec3> path;
    navMesh->getPath(start, end, path);

    foreach(glm::vec3 p, path)
    {
        std::cout << glm::to_string(p) << std::endl;
    }
}

GeometricManager::~GeometricManager()
{
    delete navMesh;
}

/* Intersection methods */
bool GeometricManager::intersectTriangles(QList<Triangle *> &ts, glm::vec3 startPos,
                                 glm::vec3 endPos, glm::vec3 dims,
                                 CollisionData &data, Triangle *&tri)
{
    glm::vec3 invDims = glm::vec3(2 / dims.x, 2 / dims.y, 2 / dims.z);

    /* Calculate direction */
    glm::vec3 scaledStart = startPos * invDims;
    glm::vec3 scaledEnd = endPos * invDims;
    glm::vec3 startDir = scaledEnd - scaledStart;

    /* Data for minimum intersection */
    CollisionData min_data;
    min_data.t = -1;

    bool intersected = false;

    /* Calculate intersection */
    foreach(Triangle *triangle, ts)
    {
        Triangle scaledTriangle = triangle->scale(invDims);
        Ray ray = Ray(scaledStart, startDir);

        if(intersectTriangle(scaledTriangle, ray, data))
        {
            if(data.t < min_data.t || min_data.t < 0)
            {
                intersected = true;

                min_data.t = data.t;
                min_data.n = data.n;
                tri = triangle;
            }
        }
    }

    data.t = min_data.t;

    // Scale normal by inverse transpose transformation
    if(glm::length2(min_data.n) > 0)
    {
        data.n = glm::normalize(min_data.n * invDims);
    }
    else
    {
        data.n = glm::vec3(0, 0, 0);
    }

    return intersected;
}

bool GeometricManager::intersectTriangle(const Triangle &triangle, Ray &ray,
                                         CollisionData &data)
{
    CollisionData min_data;
    min_data.t = -1;

    bool intersected = false;

    /* Intersect with triangle interior */
    if(ray.intersectTriangle(triangle, data))
    {
        if(data.t <= 1 && glm::dot(triangle.normal, data.n) >= 0)
        {
            intersected = true;

            min_data.t = data.t;
            min_data.n = data.n;
        }
    }

    /* Intersect with triangle edges */
    for(int i = 0; i < 3; i++)
    {
        for(int j = i + 1; j < 3; j++)
        {
            if(ray.intersectCylinder(triangle.vertices[i], triangle.vertices[j],
                                     data))
            {
                if((data.t < min_data.t || min_data.t < 0) && (data.t <= 1))
                {
                    intersected = true;

                    min_data.t = data.t;
                    min_data.n = data.n;
                }
            }
        }
    }

    /* Intersect with vertices */
    ray.setDir(-ray.getDir());

    for(int i = 0; i < 3; i++)
    {
        ray.setPos(triangle.vertices[i]);

        if(ray.intersectSphere(ray.getPos(), data))
        {
            if((data.t < min_data.t || min_data.t < 0) && (data.t <= 1))
            {
                intersected = true;

                min_data.t = data.t;
                min_data.n = data.n;
            }
        }
    }

    data.t = min_data.t;
    data.n = min_data.n;
    return intersected;
}

bool GeometricManager::intersectEnvironment(Entity *ent, glm::vec3 startPos,
                                            glm::vec3 endPos, glm::vec3 &move,
                                            CollisionData &data)
{
    Triangle *tri;

    if(intersectTriangles(m_env, startPos, endPos, ent->getDimensions(), data, tri))
    {
        glm::vec3 intPoint = startPos + data.t * move;
        glm::vec3 rem = endPos - intPoint;
        glm::vec3 parr = rem - glm::dot(rem, data.n) * data.n;

        move = rem - glm::vec3(0, 1, 0) * glm::dot(rem, data.n) / data.n.y;

        if(glm::length2(move) > 0)
        {
            move = glm::length(parr) * glm::normalize(move);
        }
        else
        {
            move = parr;
        }

        ent->setPosition(intPoint + data.n * EPS);
        return true;
    }

    return false;
}

Triangle *GeometricManager::getTriangleRay(QList<Triangle *> &triangles, Ray &ray,
                                           CollisionData &data)
{
    glm::vec3 endPos = ray.getPos();
    endPos += 100.f * ray.getDir();

    Triangle *tri;
    intersectTriangles(triangles, ray.getPos(), endPos, glm::vec3(0.5, 1, 0.5), data, tri);
    return tri;
}

Triangle *GeometricManager::getTriangleBelow(QList<Triangle *> &triangles, glm::vec3 pos,
                                             CollisionData &data)
{
    Ray ray = Ray(pos, glm::vec3(0, -1, 0));

    return getTriangleRay(triangles, ray, data);
}

void GeometricManager::moveEntity(Entity *ent, float seconds)
{
    CollisionData data;

    glm::vec3 startPos = ent->getPosition();
    std::cout << "start pos" << std::endl;
    std::cout << getTriangleBelow(navMesh->triangles, startPos, data) << std::endl;
    std::cout << "end pos" << std::endl;
    std::cout << getTriangleBelow(navMesh->triangles, glm::vec3(0, 2.5, 4), data) << std::endl;
    glm::vec3 endPos = startPos + seconds * ent->getVelocity() * ent->getSpeed();
    endPos.y = startPos.y + seconds * ent->getVelocity().y;

    glm::vec3 move = endPos - startPos;
    glm::vec3 moveXZ = glm::vec3(move.x, 0, move.z);
    glm::vec3 moveY = glm::vec3(0, move.y, 0);

    /* Collision in Y direction, no sliding */
    if(intersectEnvironment(ent, startPos, startPos + moveY, moveY, data))
    {
        glm::vec3 vel = ent->getVelocity();
        vel.y = 0;

        if(data.n.y > 0)
        {
            vel.y = -5;
            ent->setGrounded(true);
        }

        ent->setVelocity(vel);
    }
    else
    {
        if(ent->getGrounded())
        {
            glm::vec3 vel = ent->getVelocity();
            vel.y = -2;
            ent->setVelocity(vel);
        }

        ent->setGrounded(false);
        ent->setPosition(ent->getPosition() + moveY);
    }

    /* Collision in XZ, sliding */
    for(int i = 0; i < 4; i++)
    {
        startPos = ent->getPosition();

        if(!intersectEnvironment(ent, startPos, startPos + moveXZ, moveXZ, data))
        {
            break;
        }
    }

    ent->setPosition(ent->getPosition() + moveXZ);
}

void GeometricManager::onTick(float seconds)
{
    foreach(Entity *ent, m_entities)
    {
        moveEntity(ent, seconds);

        ent->onTick(seconds);
    }
}

void GeometricManager::onDraw(Graphics *graphics)
{
    navMesh->draw(graphics);

    foreach(Entity *ent, m_entities)
    {
        ent->onDraw(graphics);
    }
}
