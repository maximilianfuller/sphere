#include "engine/intersect/BoundingCylinder.h"

#include "engine/intersect/BoundingPlane.h"
#include "engine/intersect/BoundingBox.h"

BoundingCylinder::BoundingCylinder(glm::vec3 pos, float radius, float height) :
    m_radius(radius),
    m_height(height),
    BoundingShape(pos)
{
}

BoundingCylinder::~BoundingCylinder()
{
}

float BoundingCylinder::getRadius()
{
    return m_radius;
}

void BoundingCylinder::setRadius(float radius)
{
    m_radius = radius;
}

float BoundingCylinder::getHeight()
{
    return m_height;
}

void BoundingCylinder::setHeight(float height)
{
    m_height = height;
}

bool BoundingCylinder::intersect(BoundingShape *shape, glm::vec3 &mtv)
{
    return shape->intersect(this, mtv);
}

bool BoundingCylinder::intersect(BoundingPlane *plane, glm::vec3 &mtv)
{
    mtv = glm::vec3(0, plane->getLevel() - m_pos.y, 0);
    return mtv.y > 0;
}

bool BoundingCylinder::intersect(BoundingCylinder *cyl, glm::vec3 &mtv)
{
    glm::vec3 v = glm::vec3(cyl->getPosition().x - m_pos.x, 0,
                            cyl->getPosition().z - m_pos.z);
    glm::vec3 mtvRadial = (cyl->getRadius() + m_radius) * glm::normalize(v) - v;

    /* TODO: fix this, min should not be involved in this way */
    glm::vec3 mtvHeight = glm::vec3(0, glm::min(cyl->getPosition().y
                                                    + cyl->getHeight()
                                                    - m_pos.y,
                                                m_pos.y + m_height
                                                    - cyl->getPosition().y), 0);

    bool intersectRadial = v.x * v.x + v.z * v.z < (cyl->getRadius() + m_radius)
            * (cyl->getRadius() + m_radius);
    bool intersectHeight = (cyl->getPosition().y + cyl->getHeight() > m_pos.y)
            && (m_pos.y + m_height > cyl->getPosition().y);

    if(mtvRadial.x * mtvRadial.x + mtvRadial.y * mtvRadial.y
            < mtvHeight.y * mtvHeight.y)
    {
        mtv = mtvRadial;
    }
    else
    {
        mtv = mtvHeight;
    }

    return intersectRadial && intersectHeight;
}

bool BoundingCylinder::intersect(BoundingBox *box, glm::vec3 &mtv)
{
    glm::vec3 blockPos = box->getPosition();

    glm::vec3 mtvX, mtvY, mtvZ;
    bool intersectsX, intersectsY, intersectsZ;

    if(m_pos.x > blockPos.x + 1)
    {
        mtvX = glm::vec3(blockPos.x - (m_pos + glm::vec3(-m_radius, 0, 0)).x, 0, 0);
    }
    else
    {
        mtvX = glm::vec3((m_pos + glm::vec3(m_radius, 0, 0)).x - blockPos.x, 0, 0);
    }

    if(m_pos.y > blockPos.y + 1)
    {
        mtvY = glm::vec3(0, blockPos.y - (m_pos + glm::vec3(0, -m_radius, 0)).y, 0);
    }
    else
    {
        mtvY = glm::vec3(0, (m_pos + glm::vec3(0, m_radius, 0)).y - blockPos.y, 0);
    }

    if(m_pos.z > blockPos.z + 1)
    {
        mtvZ = glm::vec3(0, blockPos.z - (m_pos + glm::vec3(0, 0, -m_radius)).z, 0);
    }
    else
    {
        mtvZ = glm::vec3(0, (m_pos + glm::vec3(0, 0, m_radius)).z - blockPos.z, 0);
    }

    if(glm::abs(mtvX.x) > glm::abs(mtvY.y) && glm::abs(mtvX.x) > glm::abs(mtvZ.z))
    {
        mtv = mtvX;
    }
    else if(glm::abs(mtvY.x) > glm::abs(mtvX.y) && glm::abs(mtvY.x) > glm::abs(mtvZ.z))
    {
        mtv = mtvY;
    }
    else
    {
        mtv = mtvZ;
    }

    intersectsX = (m_pos + glm::vec3(m_radius, 0, 0)).x > blockPos.x
            && blockPos.x + 1 > (m_pos + glm::vec3(-m_radius, 0, 0)).x;

    intersectsY = (m_pos + glm::vec3(0, m_radius, 0)).y > blockPos.y
            && blockPos.y + 1 > (m_pos + glm::vec3(0, -m_radius, 0)).y;

    intersectsZ = (m_pos + glm::vec3(0, 0, m_radius)).z > blockPos.z
            && blockPos.z + 1 > (m_pos + glm::vec3(0, 0, -m_radius)).z;

    return intersectsX && intersectsY && intersectsZ;
}
