#include "warmup/world/GameWorld.h"

#include "engine/camera/PerspectiveCamera.h"

#include "warmup/entity/Player.h"
#include "warmup/entity/Floor.h"

#include <QKeyEvent>

GameWorld::GameWorld(PerspectiveCamera *camera) :
    m_camera(camera)
{
    m_player = new Player(camera, 1.0);
    addEntity(m_player);
    addEntity(new Floor());
}

GameWorld::~GameWorld()
{
}

void GameWorld::mouseMoveEvent(QMouseEvent *event, int startX,
                               int startY)
{
    int dx = event->x() - startX;
    int dy = event->y() - startY;

    m_player->rotate(dx / 100.f, -dy / 100.f);
}

void GameWorld::keyPressEvent(QKeyEvent *event)
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
        m_player->setJump(true);
    }
    else if(event->key() == Qt::Key_Shift)
    {
        m_camera->toggleThirdPerson();
    }

}

void GameWorld::keyReleaseEvent(QKeyEvent *event)
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
    else if(event->key() == Qt::Key_Space && m_player->getJump())
    {
        m_player->setJump(false);
    }
}
