#include "platformer/WelcomeScreen.h"

#include "engine/Application.h"
#include "engine/camera/SimpleCamera.h"

#include "platformer/PlatformerScreen.h"
#include "platformer/world/WelcomeWorld.h"

#include <QApplication>
#include <QKeyEvent>

WelcomeScreen::WelcomeScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    /* Setup camera */
    m_camera = dynamic_cast<Camera *>(new SimpleCamera());

    /* Setup world */
    m_world = new WelcomeWorld(m_camera);
}

WelcomeScreen::~WelcomeScreen()
{
}

void WelcomeScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::exit(0);
    }
    else if(event->key() == Qt::Key_1)
    {
        PlatformerScreen* screen = dynamic_cast<PlatformerScreen *>(m_app->getScreen(0));
        screen->setLevel(":/obj/level_easy.obj", "level_easy");
        m_app->moveScreen(this, 0);
    }
    else if(event->key() == Qt::Key_2)
    {
        PlatformerScreen* screen = dynamic_cast<PlatformerScreen *>(m_app->getScreen(0));
        screen->setLevel(":/obj/level_hard.obj", "level_hard");
        m_app->moveScreen(this, 0);
    }
    else if(event->key() == Qt::Key_3)
    {
        PlatformerScreen* screen = dynamic_cast<PlatformerScreen *>(m_app->getScreen(0));
        screen->setLevel(":/obj/level_island.obj", "level_island");
        m_app->moveScreen(this, 0);
    }
}
