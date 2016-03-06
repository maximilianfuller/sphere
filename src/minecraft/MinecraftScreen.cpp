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
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::exit(0);
    }

    Screen::keyPressEvent(event);
}

void MinecraftScreen::onTick(float seconds)
{
    Screen::onTick(seconds);
}
