#include "warmup/GameScreen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/camera/Camera.h"

#include "warmup/world/GameWorld.h"
#include "warmup/entity/Player.h"

#include <QKeyEvent>

GameScreen::GameScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    /* Setup camera */
    m_camera = new Camera();

    /* Setup world */
    m_world = dynamic_cast<World *>(new GameWorld(m_camera));
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

        Camera *temp = new Camera(m_camera->getRatio());
        delete m_camera;
        m_camera = temp;

        delete m_world;
        m_world = dynamic_cast<World *>(new GameWorld(temp));
    }

    Screen::onTick(seconds);
}
