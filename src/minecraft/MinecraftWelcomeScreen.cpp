#include "minecraft/MinecraftWelcomeScreen.h"

#include "engine/Application.h"
#include "engine/graphics/Controller.h"
#include "engine/camera/SimpleCamera.h"

#include "minecraft/manager/MinecraftManager.h"
#include "minecraft/manager/MinecraftWelcomeWorld.h"

#include <QApplication>
#include <QKeyEvent>

MinecraftWelcomeScreen::MinecraftWelcomeScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    /* Setup camera */
    m_camera = dynamic_cast<Camera *>(new SimpleCamera());

    /* Setup world */
    m_world = new MinecraftWelcomeWorld(m_camera);
}

MinecraftWelcomeScreen::~MinecraftWelcomeScreen()
{
}

void MinecraftWelcomeScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::exit(0);
    }
    else if(event->key() == Qt::Key_Enter)
    {
        m_app->getGraphics()->loadTexture("atlas", 0);
        m_app->moveScreen(this, 0);
    }
}
