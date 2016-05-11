#include "platformer/world/GameWorld.h"

#include "util/obj.h"

#include "engine/camera/Camera.h"
#include "engine/graphics/Graphics.h"
#include "engine/light/PointLight.h"
#include "engine/light/DirectionalLight.h"
#include "engine/particle/ParticleSystem.h"
#include "engine/particle/ParticleStreamSystem.h"
#include "engine/planet/planetmanager.h"

#include "engine/geom/nav/NavMesh.h"

#include "platformer/entity/Player.h"
#include "platformer/entity/Enemy.h"
#include "platformer/entity/GameEntity.h"
#include "platformer/manager/InteractionManager.h"
#include "platformer/manager/CollisionManager.h"

#include <QKeyEvent>
#include <queue>
#include <glm/gtx/rotate_vector.hpp>
#include <platformer/manager/entitymanager.h>

/* TODO
 * fix lighting
 * fix game balance
 * fix sorting
 */

GameWorld::GameWorld(Camera *camera, Graphics *graphics) :
    World(camera)
{
    /* Player */
    m_player = new Player(this, camera);
    addEntity(m_player);
    addEntity(new Enemy(this, 0.0015, glm::vec3(1, 0, 0), glm::vec3(1.002, 0, 0), 0.001));

    /* Add managers */
    addManager(new CollisionManager(this, m_entities));
    addManager(new EntityManager(this, m_entities, m_player));
    addManager(new InteractionManager(this, m_entities));

    /* Lights */
    addDirectionalLight(new DirectionalLight(glm::vec3(1, 1, 1), glm::vec3(0.1, 0.1, 0.1)*5.f));

    m_planet = new PlanetManager(graphics);
}

GameWorld::~GameWorld()
{
    delete m_planet;
}

Player *GameWorld::getPlayer()
{
    return m_player;
}

void GameWorld::mouseMoveEvent(QMouseEvent *event, int startX,
                               int startY)
{
    float yaw = -(event->x() - startX) / 300.f;
    float pitch = -(event->y() - startY) / 300.f;

    glm::vec3 look = glm::normalize(m_camera->getLook());
    glm::vec3 up = glm::normalize(m_camera->getUp());

    float pitchToUp = glm::acos(glm::dot(look, up));

    if(pitch < 0 && pitch < LOOK_ANGLE_EPS - (M_PI - pitchToUp))
    {
        pitch = (LOOK_ANGLE_EPS - (M_PI - pitchToUp));
    }
    else if(pitch > 0 && pitch > pitchToUp - LOOK_ANGLE_EPS)
    {
        pitch = pitchToUp - LOOK_ANGLE_EPS;
    }

    glm::vec3 newLook = glm::rotate(look, yaw, up);
    newLook = glm::rotate(newLook, pitch, glm::cross(look, up));
    m_camera->setLook(newLook);

    /* Update matrices */
    m_player->updateCamera();
}

void GameWorld::mousePressEvent(QMouseEvent *event)
{
    m_player->attack();
}

void GameWorld::mouseReleaseEvent(QMouseEvent *event)
{
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
    else if(event->key() == Qt::Key_Q)
    {
        m_player->setZoomOut(true);
    }
    else if(event->key() == Qt::Key_E)
    {
        m_player->setZoomIn(true);
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
    else if(event->key() == Qt::Key_Q && m_player->getZoomOut())
    {
        m_player->setZoomOut(false);
    }
    else if(event->key() == Qt::Key_E && m_player->getZoomIn())
    {
        m_player->setZoomIn(false);
    }
}

void GameWorld::onTick(float seconds)
{
    /* Set camera up vector */
    m_camera->setUp(glm::normalize(m_camera->getEye()));
    World::onTick(seconds);
}

void GameWorld::drawGeometry(Graphics *graphics)
{
    World::drawGeometry(graphics);

    graphics->sendModelUniform(glm::mat4());
    m_planet->drawPlanet(m_camera->getEye(), m_player->getPosition());
}

void GameWorld::drawLightGeometry(Graphics *graphics)
{
    /* Draw point lights */
    m_camera->setTransforms(graphics);
    m_camera->setResolution(graphics);

    /* Sort entities by depth */
    std::priority_queue<std::pair<GameEntity *,float>,
            std::vector<std::pair<GameEntity *,float> >, CompareDepth> depthQueue;

    foreach(Entity *entity, m_entities)
    {
        GameEntity *ent = dynamic_cast<GameEntity *>(entity);

        float radius = ent->getRadius();
        float dist = glm::max(glm::length(ent->getPosition() + glm::vec3(0, 1, 0)
                                          - m_camera->getEye())
                - radius, 0.f);

        std::pair<GameEntity *, float> p(ent, dist);
        depthQueue.push(p);
    }

    /* Draw entities */
    while(!depthQueue.empty())
    {
        (depthQueue.top()).first->drawLightGeometry(graphics);
        depthQueue.pop();
    }
}

float GameWorld::getTerrainHeight(glm::vec3 loc) {
    return 1.f;
    //return 1.f + m_planet->getNoise(glm::normalize(loc));
}
