#include "platformer/world/GameWorld.h"

#include "util/obj.h"

#include "engine/camera/Camera.h"
#include "engine/graphics/Graphics.h"
#include "engine/light/Light.h"
#include "engine/shape/Ellipsoid.h"
#include "engine/intersect/Ray.h"

#include "engine/geom/manager/GeometricManager.h"
#include "engine/geom/nav/NavMesh.h"

#include "platformer/entity/Player.h"

#include <QKeyEvent>

GameWorld::GameWorld(Camera *camera, Graphics *graphics,
                     QString levelFile, QString levelKey) :
    m_levelKey(levelKey),
    m_target(new Ellipsoid(glm::vec3(0, 3, 0), glm::vec3(0.5, 1, 0.5), glm::vec4(1, 0, 0, 1))),
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

    /* Add manager */
    addManager(new GeometricManager(m_level->triangles, m_level->triangleData,
                                    m_entities, graphics));

    addLight(new Light());
}

GameWorld::~GameWorld()
{
    delete m_level;
    delete m_target;
}

Player *GameWorld::getPlayer()
{
    return m_player;
}

Ray GameWorld::getRay(int mouseX, int mouseY)
{
    glm::vec2 size = m_camera->getRatio();

    /* Get film plane coordinates */
    float filmX = ((2.f * mouseX) / size.x) - 1.f;
    float filmY = 1.f - ((2.f * mouseY) / size.y);
    float filmZ = -1.f;

    /* Player position */
    glm::vec3 pos = m_player->getPosition();

    /* Get inverse matrix */
    glm::mat4x4 inverse = glm::inverse(m_camera->getPerspective());

    /* Get ray */
    glm::vec4 dir = inverse * glm::vec4(filmX, filmY, filmZ, 1);

    /*
    worldRay = glm::normalize(
                glm::vec3(m_scene->m_filmToWorld * glm::vec4(filmX, filmY, filmZ, 1.f)) - worldEye);
                */
}

void GameWorld::setTarget()
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
        m_player->setNitro(true);
    }
    else if(event->key() == Qt::Key_F1)
    {
        m_camera->toggleThirdPerson();
    }
    else if(event->key() == Qt::Key_F2)
    {
        GeometricManager *manager = dynamic_cast<GeometricManager *>(m_managers.at(0));

        manager->navMesh->toggleVisible();
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

void GameWorld::drawGeometry(Graphics *graphics)
{
    /* Draw mesh */
    graphics->sendUseLightingUniform(1);
    graphics->sendUseTextureUniform(0);
    graphics->sendModelUniform(glm::mat4x4());
    graphics->sendColorUniform(glm::vec4(1));
    graphics->drawShape(m_levelKey);

    /* Draw target */
    m_target->draw(graphics);

    World::drawGeometry(graphics);
}
