#ifndef WELCOMEMESSAGE_H
#define WELCOMEMESSAGE_H

#include "engine/entity/BackgroundEntity.h"

class WelcomeMessage : public BackgroundEntity
{
public:
    WelcomeMessage(World *world);
    ~WelcomeMessage();
};

#endif // WELCOMEMESSAGE_H
