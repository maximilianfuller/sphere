#include "Ray.h"

#include "engine/intersect/Triangle.h"

Ray::Ray(glm::vec3 p, glm::vec3 d) :
    m_pos(p),
    m_dir(d)
{
}

glm::vec3 Ray::getPos()
{
    return m_pos;
}

void Ray::setPos(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 Ray::getDir()
{
    return m_dir;
}

void Ray::setDir(glm::vec3 dir)
{
    m_dir = dir;
}

bool Ray::intersectTriangle(const Triangle &triangle, CollisionData &data)
{
    float t = -(glm::dot(triangle.normal,
                         m_pos - triangle.normal - triangle.vertices[0]))
            / (glm::dot(triangle.normal, m_dir));

    glm::vec3 intPoint = (m_pos - triangle.normal) + m_dir * t;
    glm::vec3 n1 = glm::cross(triangle.vertices[1] - triangle.vertices[0],
            intPoint - triangle.vertices[1]);
    glm::vec3 n2 = glm::cross(triangle.vertices[2] - triangle.vertices[1],
            intPoint - triangle.vertices[2]);
    glm::vec3 n3 = glm::cross(triangle.vertices[0] - triangle.vertices[2],
            intPoint - triangle.vertices[0]);

    if(glm::dot(triangle.normal, n1) > 0
            && glm::dot(triangle.normal, n2) > 0
            && glm::dot(triangle.normal, n3) > 0
            && t >= 0)
    {
        // Set normal to location of sphere at intersection minus intersection point
        data.t = t;
        data.n = (m_pos + t * m_dir) - intPoint;
        return true;
    }

    data.t = 1;
    return false;
}

bool Ray::intersectSphere(glm::vec3 center, CollisionData &data)
{
    float a = m_dir.x * m_dir.x + m_dir.y * m_dir.y + m_dir.z * m_dir.z;
    float b = (2 * m_pos.x * m_dir.x - 2 * m_dir.x * center.x)
            + (2 * m_pos.y * m_dir.y - 2 * m_dir.y * center.y)
            + (2 * m_pos.z * m_dir.z - 2 * m_dir.z * center.z);
    float c = m_pos.x * m_pos.x + m_pos.y * m_pos.y + m_pos.z * m_pos.z
            + center.x * center.x + center.y * center.y + center.z * center.z
            - 2 * m_pos.x * center.x - 2 * m_pos.y * center.y - 2 * m_pos.z * center.z - 1;

    // Set normal to center minus vertex
    data.n = center - m_pos;

    // Whether or not a solution was found
    return quadMinSolution(a, b, c, data.t);
}

bool Ray::intersectCylinder(glm::vec3 v1, glm::vec3 v2, CollisionData &data)
{
    glm::vec3 w = glm::cross(m_dir, v2 - v1);
    glm::vec3 z = glm::cross(m_pos - v1, v2 - v1);

    float a = glm::length2(w);
    float b = 2 * glm::dot(w, z);
    float c = glm::length2(z) - glm::length2(v2 - v1);

    float t = -1;

    if(quadMinSolution(a, b, c, t) )
    {
        glm::vec3 intPoint = m_pos + t * m_dir;
        float projDot = glm::dot(intPoint - v1, v2 - v1);

        if((0 < projDot) && (projDot <= glm::length2(v2 - v1)))
        {
            // Set normal to location of sphere at intersection minus intersection point
            glm::vec3 edge = glm::normalize(v2 - v1);
            data.t = t;
            data.n = intPoint - (v1 + edge * glm::dot(intPoint - v1, edge));
            return true;
        }
    }

    data.t = -1;
    return false;
}

bool Ray::quadMinSolution(float a, float b, float c, float &t)
{
    float disc = b * b - 4 * a * c;

    if(disc < 0)
    {
        t = -1;
        return false;
    }

    float t1 = (-b - glm::sqrt(disc)) / (2 * a);
    float t2 = (-b + glm::sqrt(disc)) / (2 * a);

    if(t1 > 0 && (t2 < 0 || t1 < t2))
    {
        t = t1;
        return true;
    }

    if (t2 > 0)
    {
        t = t2;
        return true;
    }

    t = -1;
    return false;
}
