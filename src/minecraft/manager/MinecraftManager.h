#ifndef MINECRAFTMANAGER_H
#define MINECRAFTMANAGER_H

#include "engine/voxel/manager/Manager.h"

class PerspectiveCamera;
class MinecraftPlayer;

class MinecraftManager : public Voxel::Manager
{
public:
    MinecraftManager(PerspectiveCamera *camera);
    ~MinecraftManager();

    MinecraftPlayer *getPlayer();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    PerspectiveCamera *m_camera;
    MinecraftPlayer *m_player;
};


#endif // MINECRAFTMANAGER_H
