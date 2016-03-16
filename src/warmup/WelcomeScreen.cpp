#include "warmup/WelcomeScreen.h"

#include "engine/Application.h"
#include "engine/camera/SimpleCamera.h"

#include "warmup/world/WelcomeWorld.h"

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

    else if(event->key() == Qt::Key_I)
    {
        m_app->moveScreen(this, 0);
    }
}
