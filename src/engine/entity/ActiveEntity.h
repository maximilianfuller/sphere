#ifndef ACTIVEENTITY_H
#define ACTIVEENTITY_H

#include "engine/entity/Entity.h"
#include "util/CommonIncludes.h"

class ActiveEntity : public Entity
{
public:
    ActiveEntity(glm::vec3 vel = glm::vec3(0, 0, 0),
                 glm::vec3 acc = glm::vec3(0, 0, 0));
    ~ActiveEntity();

    virtual EntityType getEntityType() const;

protected:
    glm::vec3 m_vel;
    glm::vec3 m_acc;
};

#endif // ACTIVEENTITY_H
