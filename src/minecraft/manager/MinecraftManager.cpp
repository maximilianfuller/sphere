#include "minecraft/manager/MinecraftManager.h"

#include "engine/camera/Camera.h"
#include "engine/voxel/chunk/Chunk.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/shape/VoxelCube.h"

#include "minecraft/entity/MinecraftPlayer.h"
#include "minecraft/terrain/ValueTerrain.h"

#include <QKeyEvent>

MinecraftManager::MinecraftManager(Camera *camera) :
    m_camera(camera),
    Manager(new ValueTerrain())
{
    m_player = new MinecraftPlayer(this, camera);
    addActiveEntity(m_player);

    /* Set up blocks */
    float step = 1.0 / 16.0;

    glm::vec2 air;
    glm::vec2 grassTopStart = glm::vec2(0, 16.0 - step);
    glm::vec2 grassTopEnd = glm::vec2(step, 16.0);
    glm::vec2 rockStart = glm::vec2(step, 16.0 - step);
    glm::vec2 rockEnd = glm::vec2(2 * step, 16.0);
    glm::vec2 dirtStart = glm::vec2(2 * step, 16.0 - step);
    glm::vec2 dirtEnd = glm::vec2(3 * step, 16.0);
    glm::vec2 grassSideStart = glm::vec2(3 * step, 16.0 - step);
    glm::vec2 grassSideEnd = glm::vec2(4 * step, 16.0);


    m_blockTypes[BLOCK_AIR] = new Block(0, new VoxelCube(air, air,
                                                         air, air,
                                                         air, air,
                                                         air, air,
                                                         air, air,
                                                         air, air));
    m_blockTypes[BLOCK_ROCK] = new Block(1, new VoxelCube(rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd));
    m_blockTypes[BLOCK_DIRT] = new Block(1, new VoxelCube(dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd));
    m_blockTypes[BLOCK_GRASS] = new Block(1, new VoxelCube(grassSideStart, grassSideEnd,
                                                           grassSideStart, grassSideEnd,
                                                           dirtStart, dirtEnd,
                                                           grassTopStart, grassTopEnd,
                                                           grassSideStart, grassSideEnd,
                                                           grassSideStart, grassSideEnd));
}

MinecraftManager::~MinecraftManager()
{
}

MinecraftPlayer *MinecraftManager::getMinecraftPlayer()
{
    return dynamic_cast<MinecraftPlayer *>(m_player);
}

void MinecraftManager::mouseMoveEvent(QMouseEvent *event, int startX,
                                      int startY)
{
    int dx = event->x() - startX;
    int dy = event->y() - startY;

    getMinecraftPlayer()->rotate(dx / 100.f, -dy / 100.f);
}

void MinecraftManager::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        getMinecraftPlayer()->setMoveFoward(true);
    }
    else if(event->key() == Qt::Key_S)
    {
        getMinecraftPlayer()->setMoveBackward(true);
    }
    else if(event->key() == Qt::Key_A)
    {
        getMinecraftPlayer()->setMoveLeft(true);
    }
    else if(event->key() == Qt::Key_D)
    {
        getMinecraftPlayer()->setMoveRight(true);
    }
    else if(event->key() == Qt::Key_Space)
    {
        getMinecraftPlayer()->setJump(true);
    }
    else if(event->key() == Qt::Key_Shift)
    {
        m_camera->toggleThirdPerson();
    }

}

void MinecraftManager::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W && getMinecraftPlayer()->getMoveFoward())
    {
        getMinecraftPlayer()->setMoveFoward(false);
    }
    else if(event->key() == Qt::Key_S && getMinecraftPlayer()->getMoveBackward())
    {
        getMinecraftPlayer()->setMoveBackward(false);
    }
    else if(event->key() == Qt::Key_A && getMinecraftPlayer()->getMoveLeft())
    {
        getMinecraftPlayer()->setMoveLeft(false);
    }
    else if(event->key() == Qt::Key_D && getMinecraftPlayer()->getMoveRight())
    {
        getMinecraftPlayer()->setMoveRight(false);
    }
    else if(event->key() == Qt::Key_Space && getMinecraftPlayer()->getJump())
    {
        getMinecraftPlayer()->setJump(false);
    }
}
