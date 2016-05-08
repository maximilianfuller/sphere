#include "platformer/WelcomeScreen.h"

#include "engine/Application.h"
#include "engine/camera/SimpleCamera.h"

#include "platformer/PlatformerScreen.h"
#include "platformer/world/WelcomeWorld.h"

#include <QApplication>
#include <QKeyEvent>

WelcomeScreen::WelcomeScreen(Application *app, int width, int height, float opacity) :
    Screen(app, opacity, width, height)
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
        m_app->moveScreen(this, 0);
    }
}
