#include "minecraft/MinecraftScreen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/camera/Camera.h"

#include "minecraft/manager/MinecraftManager.h"
#include "minecraft/entity/MinecraftPlayer.h"

#include <QApplication>
#include <QKeyEvent>

MinecraftScreen::MinecraftScreen(Application *app, float opacity) :
    Screen(app, opacity)
{
    /* Setup camera */
    m_camera = new Camera();

    /* Setup world */
    m_world = new MinecraftManager(m_camera);
}

MinecraftScreen::~MinecraftScreen()
{
}

void MinecraftScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        delete m_world;
        m_world = new MinecraftManager(m_camera);

        m_app->moveScreen(this, 0);
    }
    else if(event->key() == Qt::Key_F1)
    {
        MinecraftManager *manager = dynamic_cast<MinecraftManager *>(m_world);
        manager->setPeacefulMode(true);
    }

    Screen::keyPressEvent(event);
}

void MinecraftScreen::onTick(float seconds)
{
    MinecraftManager *manager = dynamic_cast<MinecraftManager *>(m_world);

    if(manager->getGameOver())
    {
        m_app->moveScreen(this, 0);

        delete m_world;
        m_world = new MinecraftManager(m_camera);
    }

    Screen::onTick(seconds);
}
