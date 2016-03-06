#ifndef MINECRAFTMANAGER_H
#define MINECRAFTMANAGER_H

#include "engine/voxel/manager/Manager.h"

class Camera;
class MinecraftPlayer;

class MinecraftManager : public Manager
{
public:
    MinecraftManager(Camera *camera);
    ~MinecraftManager();

    MinecraftPlayer *getMinecraftPlayer();

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    Camera *m_camera;
};


#endif // MINECRAFTMANAGER_H
