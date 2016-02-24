#include "warmup/GameScreen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/camera/PerspectiveCamera.h"

#include "warmup/world/GameWorld.h"
#include "warmup/entity/Player.h"

#include <QKeyEvent>

GameScreen::GameScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    /* Setup camera */
    m_camera = dynamic_cast<Camera *>(new PerspectiveCamera());

    /* Setup world */
    m_world = dynamic_cast<World *>(
                new GameWorld(dynamic_cast<PerspectiveCamera *>(m_camera)));
}

GameScreen::~GameScreen()
{
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_app->moveScreen(this, 0);
    }

    Screen::keyPressEvent(event);
}

void GameScreen::onTick(float seconds)
{
    GameWorld *world = dynamic_cast<GameWorld *>(m_world);

    if(world->getGameOver())
    {
        m_app->moveScreen(this, 0);

        PerspectiveCamera *temp = new PerspectiveCamera(m_camera->getRatio());
        delete m_camera;
        m_camera = dynamic_cast<Camera *>(temp);

        delete m_world;
        m_world = dynamic_cast<World *>(new GameWorld(temp));
    }

    Screen::onTick(seconds);
}
