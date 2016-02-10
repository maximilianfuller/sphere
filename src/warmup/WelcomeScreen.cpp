#include "warmup/WelcomeScreen.h"

#include "engine/Application.h"
#include "engine/camera/SimpleCamera.h"
#include "engine/graphics/Controller.h"

#include "warmup/world/WelcomeWorld.h"

#include <QApplication>
#include <QKeyEvent>

HomeScreen::HomeScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    // Setup graphics object
    m_graphics = new Graphics::Controller();
    m_graphics->createProgram(":/shaders/shader.vert", ":/shaders/shader.frag", "default");
    m_graphics->createTexture(":/images/welcome.jpg", "welcome");

    // Setup camera
    m_camera = dynamic_cast<Camera *>(new SimpleCamera());

    // Setup world
    m_world = new WelcomeWorld();
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::exit(0);
    }

    else if(event->key() == Qt::Key_W)
    {
        m_app->moveScreen(this, 0);
    }
}
