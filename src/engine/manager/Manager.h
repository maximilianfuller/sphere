#ifndef MANAGER_H
#define MANAGER_H

#include <QList>

#include <queue>
#include <vector>

class Graphics;
class Entity;
class CompareDepth;
class PointLight;

class Manager
{
public:
    Manager(QList<Entity *> &entities);

    virtual void onTick(float seconds);
    virtual void drawGeometry(Graphics *graphics);
    virtual void drawLights(Graphics *graphics);
    virtual void drawParticles(Graphics *graphics);
    virtual void getLightGeometry(Graphics *graphics,
                                  std::priority_queue<std::pair<PointLight *,float>,
                                      std::vector<std::pair<PointLight *,float> >,
                                      CompareDepth> &depthQueue);

protected:
    QList<Entity *> &m_entities;
};

#endif // MANAGER_H
