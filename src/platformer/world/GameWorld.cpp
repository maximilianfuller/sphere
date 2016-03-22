#include "platformer/world/GameWorld.h"

#include "util/obj.h"

#include "engine/camera/Camera.h"
#include "engine/graphics/Controller.h"
#include "engine/geom/manager/GeometricManager.h"

#include "platformer/entity/Player.h"

#include <QKeyEvent>

GameWorld::GameWorld(Camera *camera, Graphics::Controller *graphics,
                     QString levelFile, QString levelKey) :
    m_levelKey(levelKey),
    World(camera)
{
    m_player = new Player(this, camera);
    addEntity(m_player);

    /* Create mesh data */
    m_level = new OBJ(levelFile);

    if(!graphics->hasShape(levelKey))
    {
        graphics->createShape(m_level->vboData.data(),
                              m_level->vboData.size() * sizeof(float),
                              m_level->vertexCount, levelKey);
    }

    graphics->loadTexture(levelKey, 0);

    /* Add manager */
    addManager(new GeometricManager(m_level->triangles, m_entities));

}

GameWorld::~GameWorld()
{
    delete m_level;
}

Player *GameWorld::getPlayer()
{
    return m_player;
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
        m_player->setNitro(true);
    }
    else if(event->key() == Qt::Key_F1)
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
    else if(event->key() == Qt::Key_Shift && m_player->getNitro())
    {
        m_player->setNitro(false);
    }
}

void GameWorld::onTick(float seconds)
{
    World::onTick(seconds);
}

void GameWorld::onDraw(Graphics::Controller *graphics)
{
    graphics->sendUseTextureUniform(1, "default");
    graphics->sendModelUniform(glm::mat4x4(), "default");
    graphics->drawShape(m_levelKey);

    World::onDraw(graphics);
}
