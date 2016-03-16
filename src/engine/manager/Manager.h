#ifndef MANAGER_H
#define MANAGER_H

#include <QList>

namespace Graphics
{
class Controller;
}
class Entity;

class Manager
{
public:
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);
};

#endif // MANAGER_H
