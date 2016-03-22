#include "minecraft/manager/MinecraftManager.h"

#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"

#include "engine/voxel/chunk/Chunk.h"
#include "engine/voxel/block/Block.h"
#include "engine/voxel/shape/VoxelCube.h"

#include "minecraft/terrain/ValueTerrain.h"
#include "minecraft/entity/MinecraftPlayer.h"
#include "minecraft/entity/MinecraftEnemy.h"

#include <QKeyEvent>

MinecraftManager::MinecraftManager(Camera *camera) :
    m_spawnCounter(200),
    m_gameOver(false),
    m_peacefulMode(false),
    VoxelManager(camera, new ValueTerrain())
{
    m_player = new MinecraftPlayer(this, camera);
    addEntity(m_player);

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


    m_blocks[BLOCK_AIR] = new Block(0, new VoxelCube(air, air,
                                                         air, air,
                                                         air, air,
                                                         air, air,
                                                         air, air,
                                                         air, air));
    m_blocks[BLOCK_ROCK] = new Block(1, new VoxelCube(rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd,
                                                          rockStart, rockEnd));
    m_blocks[BLOCK_DIRT] = new Block(1, new VoxelCube(dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd,
                                                          dirtStart, dirtEnd));
    m_blocks[BLOCK_GRASS] = new Block(1, new VoxelCube(grassSideStart, grassSideEnd,
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

bool MinecraftManager::getGameOver()
{
    return m_gameOver;
}

void MinecraftManager::setGameOver(bool val)
{
    m_gameOver = val;
}

void MinecraftManager::setPeacefulMode(bool val)
{
    m_peacefulMode = val;

    QMutableListIterator<Entity *> e(m_entities);

    while(e.hasNext())
    {
        Entity *ent = e.next();

        if(ent != m_player)
        {
            e.remove();
            delete ent;
        }
    }
}

void MinecraftManager::mouseMoveEvent(QMouseEvent *event, int startX,
                                      int startY)
{
    int dx = event->x() - startX;
    int dy = event->y() - startY;

    getMinecraftPlayer()->rotate(dx / 100.f, -dy / 100.f);
}

void MinecraftManager::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        removeBlock();
    }
    else if(event->buttons() & Qt::RightButton)
    {
        addBlock();
    }
}

void MinecraftManager::mouseReleaseEvent(QMouseEvent *event)
{
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

void MinecraftManager::removeBlock()
{
    Chunk *ret = NULL;

    foreach(Chunk *chunk, m_chunks)
    {
        if(chunk->inChunk(m_selectedPos.x, m_selectedPos.y, m_selectedPos.z))
        {
            ret = chunk;
        }
    }

    if(ret)
    {
        glm::vec3 chunkPos = ret->getPosition();
        int newX = m_selectedPos.x - chunkPos.x;
        int newY = m_selectedPos.y - chunkPos.y;
        int newZ = m_selectedPos.z - chunkPos.z;

        ret->setBlockPointer(newX, newY, newZ, BLOCK_AIR);
        ret->updateBlockVertexBuffer();
    }
}

void MinecraftManager::addBlock()
{
    Chunk *ret = NULL;

    glm::vec3 selectedPos = m_selectedPos;

    if(m_selectedFace == LeftFace)
    {
        selectedPos.x -= 1;
    }
    else if(m_selectedFace == RightFace)
    {
        selectedPos.x += 1;
    }
    else if(m_selectedFace == BottomFace)
    {
        selectedPos.y -= 1;
    }
    else if(m_selectedFace == TopFace)
    {
        selectedPos.y += 1;
    }
    else if(m_selectedFace == BackFace)
    {
        selectedPos.z -= 1;
    }
    else if(m_selectedFace == FrontFace)
    {
        selectedPos.z += 1;
    }

    foreach(Chunk *chunk, m_chunks)
    {
        if(chunk->inChunk(selectedPos.x, selectedPos.y, selectedPos.z))
        {
            ret = chunk;
        }
    }

    if(ret)
    {
        glm::vec3 chunkPos = ret->getPosition();

        int newX = selectedPos.x - chunkPos.x;
        int newY = selectedPos.y - chunkPos.y;
        int newZ = selectedPos.z - chunkPos.z;

        ret->setBlockPointer(newX, newY, newZ, BLOCK_DIRT);
        ret->updateBlockVertexBuffer();
    }
}

void MinecraftManager::spawnEnemy()
{
    m_spawnCounter = 200;

    float angle = (rand() % 360) * (M_PI / 180);
    glm::vec3 enemyPos = m_player->getPosition()
            + glm::vec3(glm::cos(angle) * 20.f, 10, glm::sin(angle) * 20.f);
    enemyPos.y = glm::min(enemyPos.y, 50.f);

    addEntity(new MinecraftEnemy(this, enemyPos));
}

void MinecraftManager::onTick(float seconds)
{
    /* Spawn a new zombie */
    if(--m_spawnCounter <= 0 && !m_peacefulMode)
    {
        spawnEnemy();
    }

    VoxelManager::onTick(seconds);
}
