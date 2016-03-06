#include "engine/intersect/BoundingCylinder.h"

BoundingCylinder::BoundingCylinder(glm::vec3 pos, glm::vec3 dims) :
    BoundingShape(pos, dims)
{
}

BoundingCylinder::~BoundingCylinder()
{
}

bool BoundingCylinder::intersect(BoundingShape *shape, glm::vec3 &mtv)
{
    return shape->intersect(this, mtv);
}

bool BoundingCylinder::intersect(BoundingCylinder *cyl, glm::vec3 &mtv)
{
    glm::vec3 cylPos = cyl->getPosition();
    glm::vec3 cylDims = cyl->getDimensions();

    glm::vec3 v = glm::vec3(cylPos.x - m_pos.x, 0, cylPos.z - m_pos.z);
    glm::vec3 mtvRadial = (cylDims.x / 2 + m_dims.x / 2) * glm::normalize(v) - v;

    /* TODO: fix this, min should not be involved in this way */
    glm::vec3 mtvHeight;
    mtvHeight.y = glm::min(cylPos.y + cylDims.y - m_pos.y,
                           m_pos.y + m_dims.y - cylPos.y);

    bool intersectRadial = v.x * v.x + v.z * v.z < (cylDims.x / 2 + m_dims.x / 2)
            * (cylDims.x / 2 + m_dims.x / 2);
    bool intersectHeight = (cylPos.y + cylDims.y > m_pos.y)
            && (m_pos.y + m_dims.y > cylPos.y);

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
