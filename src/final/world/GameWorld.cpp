#include "final/world/GameWorld.h"

#include "engine/camera/Camera.h"
#include "engine/graphics/Graphics.h"
#include "engine/geom/manager/GeometricManager.h"

#include <QKeyEvent>

GameWorld::GameWorld(Camera *camera) :
    World(camera)
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::mouseMoveEvent(QMouseEvent *event, int startX,
                               int startY)
{
    int dx = event->x() - startX;
    int dy = event->y() - startY;

    float yaw = m_camera->getYaw();
    float pitch = m_camera->getPitch();

    yaw += dx / 100.f;
    pitch += -dy / 100.f;
    pitch = glm::clamp((double)pitch, -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);

    m_camera->rotate(yaw, pitch);
}

void GameWorld::keyPressEvent(QKeyEvent *event)
{
}

void GameWorld::keyReleaseEvent(QKeyEvent *event)
{
}

void GameWorld::onTick(float seconds)
{
}

void GameWorld::drawGeometry(Graphics *graphics)
{
}
