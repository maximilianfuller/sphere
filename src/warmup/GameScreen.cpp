#include "warmup/GameScreen.h"

#include "engine/camera/Camera.h"
#include "engine/camera/PerspectiveCamera.h"
#include "engine/graphics/Controller.h"
#include "engine/Application.h"

#include "warmup/world/GameWorld.h"
#include "warmup/entity/Player.h"

#include <QKeyEvent>

GameScreen::GameScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    // Setup graphics object
    m_graphics = new Graphics::Controller();
    m_graphics->createProgram(":/shaders/shader.vert", ":/shaders/shader.frag", "default");
    m_graphics->createTexture(":/images/grass.png", "grass");

    // Setup camera
    m_camera = dynamic_cast<Camera *>(new PerspectiveCamera());

    // Setup world
    m_world = dynamic_cast<World *>(new GameWorld(
                                        dynamic_cast<PerspectiveCamera *>(m_camera)));
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
