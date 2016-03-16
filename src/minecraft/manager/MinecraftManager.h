#ifndef MINECRAFTMANAGER_H
#define MINECRAFTMANAGER_H

#include "engine/voxel/manager/VoxelManager.h"

class Camera;
class MinecraftPlayer;

class MinecraftManager : public VoxelManager
{
public:
    MinecraftManager(Camera *camera);
    ~MinecraftManager();

    MinecraftPlayer *getMinecraftPlayer();

    bool getGameOver();
    void setGameOver(bool val);

    void setPeacefulMode(bool val);

    /* Events */
    virtual void mouseMoveEvent(QMouseEvent *event, int startX,
                                int startY);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Actions */
    void removeBlock();
    void addBlock();
    void spawnEnemy();

    /* Game loop */
    void onTick(float seconds);

private:
    int m_spawnCounter;
    bool m_gameOver;
    bool m_peacefulMode;
};


#endif // MINECRAFTMANAGER_H
