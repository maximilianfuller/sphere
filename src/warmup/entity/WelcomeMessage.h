#ifndef WELCOMEMESSAGE_H
#define WELCOMEMESSAGE_H

#include "engine/entity/Entity.h"

class WelcomeMessage : public Entity
{
public:
    WelcomeMessage();
    ~WelcomeMessage();

    unsigned int getEntityType();
    bool hasIntersection(Entity *ent);
    void intersect(unsigned int e);
    void tick(float seconds);
};

#endif // WELCOMEMESSAGE_H
