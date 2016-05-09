#include "platformer/PlatformerScreen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/graphics/Graphics.h"

#include "platformer/world/GameWorld.h"

#include <QApplication>
#include <QKeyEvent>

PlatformerScreen::PlatformerScreen(Application *app, int width, int height,
                                   float opacity, Graphics *graphics) :
    m_graphics(graphics),
    Screen(app, opacity, width, height)
{
    /* Setup camera */
    m_camera = new Camera();

    /* Setup world */
    m_world = new GameWorld(m_camera, graphics);
}

PlatformerScreen::~PlatformerScreen()
{
}

void PlatformerScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::exit(0);
    }

    Screen::keyPressEvent(event);
}

void PlatformerScreen::onTick(float seconds)
{
    Screen::onTick(seconds);
}
