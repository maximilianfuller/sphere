#include "warmup/world/GameWorld.h"

#include "engine/camera/Camera.h"

#include "warmup/entity/Player.h"
#include "warmup/entity/Floor.h"
#include "warmup/entity/Zombie.h"
#include "warmup/entity/Bomb.h"

#include <QKeyEvent>

GameWorld::GameWorld(Camera *camera) :
    m_camera(camera),
    m_spawnCounter(30),
    m_numLeft(40),
    m_numSpawned(0),
    m_numTotal(40),
    m_over(false)
{
    m_player = new Player(this, camera, 1.0);
    addActiveEntity(m_player);
    addBackgroundEntity(new Floor(this));

    std::cout << m_numLeft << " zombies left." << std::endl;
}

GameWorld::~GameWorld()
{
}

Player *GameWorld::getPlayer()
{
    return m_player;
}

bool GameWorld::getGameOver()
{
    return m_over;
}

void GameWorld::setGameOver(bool val)
{
    if(m_numLeft == 0)
    {
        std::cout << "You win!" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "You lose :(" << std::endl;
        std::cout << std::endl;
    }

    m_over = val;
}

void GameWorld::spawnZombie()
{
    m_spawnCounter = 60;

    float angle = (rand() % 360) * (M_PI / 180);
    glm::vec3 zombiePos = glm::vec3(glm::cos(angle) * 14.f, 2, glm::sin(angle) * 14.f);

    addActiveEntity(new Zombie(this, zombiePos, 1.5));
}

void GameWorld::removeZombie()
{
    m_numLeft--;
    std::cout << m_numLeft << " zombies left." << std::endl;
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
    else if(event->key() == Qt::Key_1)
    {
        m_player->setPlaceBomb(true);
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
    else if(event->key() == Qt::Key_1)
    {
        m_player->setPlaceBomb(false);
    }
}

void GameWorld::onTick(float seconds)
{
    /* Check win condition */
    if(m_numLeft == 0)
    {
        setGameOver(true);
        return;
    }

    /* Spawn a new zombie */
    if(--m_spawnCounter <= 0 && ++m_numSpawned <= m_numTotal)
    {
        spawnZombie();
    }

    World::onTick(seconds);
}
