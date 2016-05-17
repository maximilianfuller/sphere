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
#include "engine/particle/ParticleTube.h"

#include <QKeyEvent>
#include <QWheelEvent>
#include <QList>
#include <QMutableListIterator>
#include <queue>
#include <glm/gtx/rotate_vector.hpp>
#include <platformer/manager/entitymanager.h>

/* TODO
 * fix lighting
 * fix game balance
 */

GameWorld::GameWorld(Camera *camera, Graphics *graphics) :
    m_stopped(true),
    m_dead(false),
    World(camera)
{
    /* Planet */
    m_planet = new PlanetManager(graphics);

    /* Create player */
    m_player = new Player(this, m_camera);
    addEntity(m_player);
    glm::vec3 southPole = glm::normalize(glm::vec3(1.f, 1.f,1.f));
    glm::vec3 startPos = (getTerrainHeight(southPole) + .01f) * southPole;
    m_player->setPosition(startPos);
    addEntity(m_player);

    /* North and south poles */
    glm::vec3 sp = glm::normalize(glm::vec3(1, 1, 1));
    glm::vec3 ep = glm::normalize(glm::vec3(-1, -1, -1));

    m_northSystem = new ParticleTube("particle", sp, sp + 100.f * sp,
                                     glm::vec3(1, 1, 1), 0.05f, 0.001f);
    m_southSystem = new ParticleTube("particle", ep, ep + 100.f * ep,
                                     glm::vec3(1, 1, 1), 0.05f, 0.001f);
    m_northSystem->start();
    m_southSystem->start();

    /* Add managers */
    addManager(new CollisionManager(this, m_entities));
    addManager(new EntityManager(this, m_entities, m_player));
    addManager(new InteractionManager(this, m_entities));

    /* Lights */
    addDirectionalLight(new DirectionalLight(glm::vec3(1, 1, 1), glm::vec3(0.1, 0.1, 0.1)));
    addDirectionalLight(new DirectionalLight(glm::vec3(-1, -1, -1), glm::vec3(0.1, 0.1, 0.1)));
}

GameWorld::~GameWorld()
{
    delete m_planet;
    delete m_northSystem;
    delete m_southSystem;
}

Player *GameWorld::getPlayer()
{
    return m_player;
}

void GameWorld::stop()
{
    m_stopped = true;
    m_dead = false;
}

bool GameWorld::getStopped()
{
    return m_stopped;
}

void GameWorld::start()
{
    m_stopped = false;
    m_dead = false;
}

void GameWorld::mouseMoveEvent(QMouseEvent *event, int startX,
                               int startY)
{
    float yaw = -(event->x() - startX) / 300.f;
    float pitch = -(event->y() - startY) / 300.f;

    if(yaw > M_PI / 6)
    {
        yaw = 0;
    }

    if(pitch > M_PI / 6)
    {
        pitch = 0;
    }

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

    if(m_stopped)
    {
        start();
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

void GameWorld::wheelEvent(QWheelEvent *event)
{
    float zoom = m_player->getZoom();

    if(event->delta() > 0 && zoom * m_player->getRadius() > MIN_ZOOM)
    {
        zoom -= 0.001 * event->delta() * zoom;
    }
    else if(event->delta() <= 0 && zoom * m_player->getRadius() < MAX_ZOOM)
    {
        zoom -= 0.001 * event->delta() * zoom;
    }

    m_player->setZoom(zoom);
}

void GameWorld::onTick(float seconds)
{
    /*
    if(m_stopped)
    {
        if(!m_dead)
        {
            m_player->setPosition(glm::normalize(glm::vec3(1, 1, 1)));
            m_player->setPower(30.0);
            m_camera->setLook(glm::normalize(glm::vec3(-1, -1, -1)));

            QMutableListIterator<Entity *> i(m_entities);

            while(i.hasNext())
            {
                Entity *ent = i.next();

                if(ent != m_player)
                {
                    delete ent;
                    i.remove();
                }
            }

            EntityManager *entManager = dynamic_cast<EntityManager *>(m_managers[1]);

            for(int i = 0; i < 200; i++)
            {
                entManager->spawnEnemy(rand() % 6 + 1);
            }

            m_dead = true;
        }

        m_camera->setEye(glm::vec3(2, 2, 2));
        m_camera->setUp(glm::vec3(-1, 1, -1));
    }
    else
    {
        if(!m_dead)
        {
            std::cout << "here" << std::endl;
            m_player->setZoom(5);
            m_player->setPower(0.002);
            m_player->setVelocity(glm::vec3(0, 0, 0));
            m_player->setGoalVelocity(glm::vec3(0, 0, 0));

            glm::vec3 southPole = glm::normalize(glm::vec3(1.f, 1.f,1.f));
            glm::vec3 startPos = (getTerrainHeight(southPole) + .01f) * southPole;
            m_player->setPosition(startPos);

            QMutableListIterator<Entity *> i(m_entities);

            while(i.hasNext())
            {
                Entity *ent = i.next();

                if(ent != m_player)
                {
                    delete ent;
                    i.remove();
                }
            }

            m_dead = true;
        }
        */

        /* Set camera up vector */
        m_camera->setUp(glm::normalize(m_camera->getEye()));

        World::onTick(seconds);
    //}
}

void GameWorld::drawGeometry(Graphics *graphics)
{
    World::drawGeometry(graphics);

    graphics->sendModelUniform(glm::mat4());
    m_planet->drawPlanet(m_camera->getEye(), m_player->getPosition());
}

void GameWorld::drawLights(Graphics *graphics)
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

        float radius = ent->getLightRadius();
        float dist = glm::abs(glm::length(ent->getPosition() - m_camera->getEye()) - radius);

        std::pair<GameEntity *, float> p(ent, dist);
        depthQueue.push(p);
    }

    /* Draw entities */
    while(!depthQueue.empty())
    {
        (depthQueue.top()).first->drawLights(graphics);
        depthQueue.pop();
    }

    graphics->sendEmptyMatrices();
    m_camera->setResolution(graphics);

    /* Draw directional lights */
    foreach(DirectionalLight *light, m_directionalLights)
    {
        light->draw(graphics);
    }
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
        float dist = glm::abs(glm::length(ent->getPosition() - m_camera->getEye()) - radius);

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
    return 1.f + m_planet->getNoise(glm::normalize(loc));
}
