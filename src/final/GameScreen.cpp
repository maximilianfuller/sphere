#include "final/GameScreen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/graphics/Graphics.h"

#include "final/world/GameWorld.h"

#include <QApplication>
#include <QKeyEvent>

GameScreen::GameScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    /* Setup camera */
    m_camera = new Camera();

    /* Setup world */
    m_world = new GameWorld(m_camera);
}

GameScreen::~GameScreen()
{
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::exit(0);
    }

    Screen::keyPressEvent(event);
}
