#ifndef SCENE_H
#define SCENE_H

#include "util/CommonIncludes.h"
#include <QList>

namespace Graphics
{
class Controller;
}
class ActiveEntity;
class BackgroundEntity;

class World
{
public:
    World();
    virtual ~World();

    /* Entity management */
    int getNumActiveEntities();
    ActiveEntity *getActiveEntity(int index);
    void addActiveEntity(ActiveEntity *ent);
    void removeActiveEntity(ActiveEntity *ent);

    int getNumBackgroundEntities();
    BackgroundEntity *getBackgroundEntity(int index);
    void addBackgroundEntity(BackgroundEntity *ent);
    void removeBackgroundEntity(BackgroundEntity *ent);

    /* Game Loop */
    virtual void onTick(float seconds);
    virtual void onDraw(Graphics::Controller *graphics);

    /* Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    QList<ActiveEntity *> m_activeEntities;
    QList<BackgroundEntity *> m_backgroundEntities;
};

#endif // SCENE_H
