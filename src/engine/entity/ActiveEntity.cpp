#include "ActiveEntity.h"

ActiveEntity::ActiveEntity(glm::vec3 vel, glm::vec3 acc) :
    m_vel(vel),
    m_acc(acc)
{
}

ActiveEntity::~ActiveEntity()
{

}

EntityType ActiveEntity::getEntityType() const
{
    return ActiveType;
}
