#include "platformer/world/GameWorld.h"

#include "util/obj.h"

#include "engine/camera/Camera.h"
#include "engine/graphics/Graphics.h"
#include "engine/light/PointLight.h"
#include "engine/light/DirectionalLight.h"
#include "engine/shape/Ellipsoid.h"
#include "engine/intersect/Ray.h"
#include "engine/intersect/Triangle.h"
#include "engine/particle/ParticleSystem.h"
#include "engine/particle/ParticleStreamSystem.h"

#include "engine/geom/manager/GeometricManager.h"
#include "engine/geom/nav/NavMesh.h"

#include "platformer/entity/Player.h"

#include <QKeyEvent>

GameWorld::GameWorld(Camera *camera, Graphics *graphics,
                     QString levelFile, QString levelKey) :
    m_levelKey(levelKey),
    m_target(new Ellipsoid(glm::vec3(0, 10, 10), glm::vec3(0.5, 1, 0.5), glm::vec4(1, 0, 1, 0.7))),
    m_ray(Ray(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1))),
    m_navFeatures(false),
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
    addManager(new GeometricManager(m_level->triangles, m_entities, graphics));

    /* Lights */
    /*
    addPointLight(new PointLight(glm::vec3(10, 4, 0), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 0, 1), 1));
    addPointLight(new PointLight(glm::vec3(-10, 4, 0), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 1, 1), 2));
    addPointLight(new PointLight(glm::vec3(-5, 4, 0), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 0, 0), 3));
    addPointLight(new PointLight(glm::vec3(0, 4, 0), glm::vec3(0.1, 0.2, 0.2), glm::vec3(0, 1, 0), 4));
    addPointLight(new PointLight(glm::vec3(5, 4, 0), glm::vec3(0.1, 0.2, 0.2), glm::vec3(0, 0, 1), 5));

    addPointLight(new PointLight(glm::vec3(10, 4, 4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 0, 1), 6));
    addPointLight(new PointLight(glm::vec3(-10, 4, 4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 1, 1), 7));
    addPointLight(new PointLight(glm::vec3(-5, 4, 4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 0, 0), 8));
    addPointLight(new PointLight(glm::vec3(0, 4, 4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(0, 1, 0), 9));
    addPointLight(new PointLight(glm::vec3(5, 4, 4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(0, 0, 1), 10));

    addPointLight(new PointLight(glm::vec3(10, 4, -4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 0, 1), 11));
    addPointLight(new PointLight(glm::vec3(-10, 4, -4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 1, 1), 12));
    addPointLight(new PointLight(glm::vec3(-5, 4, -4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(1, 0, 0), 13));
    addPointLight(new PointLight(glm::vec3(0, 4, -4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(0, 1, 0), 14));
    addPointLight(new PointLight(glm::vec3(5, 4, -4), glm::vec3(0.1, 0.2, 0.2), glm::vec3(0, 0, 1), 15));
    */

    addDirectionalLight(new DirectionalLight(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01), 1000));
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

void GameWorld::setRay()
{
    /* Player position */
    glm::vec3 pos = m_camera->getEye();

    /* Get inverse matrix */
    glm::mat4x4 inverse = glm::inverse(m_camera->getPerspective());

    /* Get position on film plane */
    glm::vec4 filmPos = inverse * glm::vec4(0, 0, -1, 1);

    m_ray = Ray(pos, RAY_LEN * glm::normalize(glm::vec3(filmPos) / filmPos.w - pos));
}

void GameWorld::setTarget()
{
    GeometricManager *manager = dynamic_cast<GeometricManager *>(m_managers.at(0));

    CollisionData dataT;
    Triangle *tri = manager->getTriangleRay(manager->navMesh->triangles, m_ray, dataT);

    CollisionData dataS;
    glm::vec3 dims = m_target->getDimensions();
    glm::vec3 invDims = glm::vec3(2 / dims.x, 2 / dims.y, 2 / dims.z);
    Ray temp = Ray(m_ray.getPos() * invDims, m_ray.getDir() * invDims);

    if(temp.intersectSphere(m_target->getPosition() * invDims, dataS))
    {
        m_target->setPosition(m_ray.getPos() + (dataS.t - 0.01f) * m_ray.getDir());
    }
    else if(tri)
    {
        m_target->setPosition(m_ray.getPos() + dataT.t * m_ray.getDir());
    }
}

void GameWorld::makePath()
{
    GeometricManager *manager = dynamic_cast<GeometricManager *>(m_managers.at(0));

    glm::vec3 eps = glm::vec3(0, 0.01, 0);

    CollisionData dataS, dataE;
    Triangle *start = manager->getTriangleBelow(manager->navMesh->triangles, m_player->getPosition() + eps, dataS);
    Triangle *end = manager->getTriangleBelow(manager->navMesh->triangles, m_target->getPosition() + eps, dataE);

    QList<glm::vec3> path;

    if(start && end)
    {
        manager->navMesh->getPath(m_player->getPosition() + dataS.t * glm::vec3(0, -RAY_LEN, 0),
                                  m_target->getPosition() + dataE.t * glm::vec3(0, -RAY_LEN, 0),
                                  start, end, path);
    }

    foreach(Ellipsoid *ell, m_targetPath)
    {
        delete(ell);
    }

    m_targetPath.clear();

    for(int i = 1; i < path.size() - 1; i++)
    {
        m_targetPath.append(new Ellipsoid(path[i], glm::vec3(0.5, 1, 0.5), glm::vec4(1, 0, 0, 0.5)));
    }
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

        m_navFeatures = !m_navFeatures;
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

void GameWorld::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_navFeatures)
    {
        setTarget();
    }
}

void GameWorld::onTick(float seconds)
{
    if(m_navFeatures)
    {
        setRay();
        makePath();
    }

    World::onTick(seconds);
}

void GameWorld::drawGeometry(Graphics *graphics)
{
    /* Draw mesh */
    graphics->sendUseLightingUniform(0);
    graphics->sendUseTextureUniform(0);
    graphics->sendModelUniform(glm::mat4x4());
    graphics->sendColorUniform(glm::vec4(1));
    graphics->drawShape(m_levelKey);

    /* Draw target */
    if(m_navFeatures)
    {
        GeometricManager *manager = dynamic_cast<GeometricManager *>(m_managers.at(0));
        manager->navMesh->draw(graphics);

        foreach(Ellipsoid *ell, m_targetPath)
        {
            ell->draw(graphics);
        }

        m_target->draw(graphics);
    }

    World::drawGeometry(graphics);
}
