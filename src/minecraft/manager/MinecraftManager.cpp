#include "minecraft/manager/MinecraftManager.h"

#include "engine/camera/PerspectiveCamera.h"
#include "engine/voxel/chunk/Chunk.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/shape/VoxelCube.h"

#include "minecraft/entity/MinecraftPlayer.h"
#include "minecraft/terrain/ValueTerrain.h"

#include <QKeyEvent>

MinecraftManager::MinecraftManager(PerspectiveCamera *camera) :
    m_camera(camera)
{
    m_player = new MinecraftPlayer(this, camera, 1.0);
    addActiveEntity(m_player);

    /* Setup chunks */
    ValueTerrain terrain = ValueTerrain();

    m_chunks[0] = new Chunk(this, &terrain, glm::vec3(-CHUNK_SIZE, 0, -CHUNK_SIZE));
    m_chunks[1] = new Chunk(this, &terrain, glm::vec3(0, 0, -CHUNK_SIZE));
    m_chunks[2] = new Chunk(this, &terrain, glm::vec3(-CHUNK_SIZE, 0, 0));
    m_chunks[3] = new Chunk(this, &terrain, glm::vec3(0, 0, 0));

    /* Set up blocks */
    float step = 1.0 / 16.0;

    // texture coordinates
    glm::vec2 air;
    glm::vec2 grassTopStart = glm::vec2(0, 16.0 - step);
    glm::vec2 grassTopEnd = glm::vec2(step, 16.0);
    glm::vec2 rockStart = glm::vec2(step, 16.0 - step);
    glm::vec2 rockEnd = glm::vec2(2 * step, 16.0);
    glm::vec2 dirtStart = glm::vec2(2 * step, 16.0 - step);
    glm::vec2 dirtEnd = glm::vec2(3 * step, 16.0);
    glm::vec2 grassSideStart = glm::vec2(3 * step, 16.0 - step);
    glm::vec2 grassSideEnd = glm::vec2(4 * step, 16.0);


    // block faces
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
    delete m_chunks[0];
    delete m_chunks[1];
    delete m_chunks[2];
    delete m_chunks[3];
}

MinecraftPlayer *MinecraftManager::getPlayer()
{
    return m_player;
}

void MinecraftManager::mouseMoveEvent(QMouseEvent *event, int startX,
                                      int startY)
{
    int dx = event->x() - startX;
    int dy = event->y() - startY;

    m_player->rotate(dx / 100.f, -dy / 100.f);
}

void MinecraftManager::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        m_player->setMoveFoward(true);
    }
    else if(event->key() == Qt::Key_S)
    {
        m_player->setMoveBackward(true);
    }
    else if(event->key() == Qt::Key_A)
    {
        m_player->setMoveLeft(true);
    }
    else if(event->key() == Qt::Key_D)
    {
        m_player->setMoveRight(true);
    }
    else if(event->key() == Qt::Key_Space)
    {
        m_player->setMoveUp(true);
    }
    else if(event->key() == Qt::Key_Shift)
    {
        m_player->setMoveDown(true);
    }
    else if(event->key() == Qt::Key_1)
    {
        m_camera->toggleThirdPerson();
    }

}

void MinecraftManager::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W && m_player->getMoveFoward())
    {
        m_player->setMoveFoward(false);
    }
    else if(event->key() == Qt::Key_S && m_player->getMoveBackward())
    {
        m_player->setMoveBackward(false);
    }
    else if(event->key() == Qt::Key_A && m_player->getMoveLeft())
    {
        m_player->setMoveLeft(false);
    }
    else if(event->key() == Qt::Key_D && m_player->getMoveRight())
    {
        m_player->setMoveRight(false);
    }
    else if(event->key() == Qt::Key_Space && m_player->getMoveUp())
    {
        m_player->setMoveUp(false);
    }
    else if(event->key() == Qt::Key_Shift && m_player->getMoveDown())
    {
        m_player->setMoveDown(false);
    }
}
