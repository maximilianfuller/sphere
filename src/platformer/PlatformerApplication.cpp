#include "platformer/PlatformerApplication.h"

#include "engine/graphics/Graphics.h"

#include "platformer/PlatformerScreen.h"
#include "platformer/WelcomeScreen.h"

#include <QKeyEvent>

PlatformerApplication::PlatformerApplication(QGLWidget *container) :
    Application(container, true, true, true, glm::vec4(0, 0, 0, 0))
{
    /* Setup graphics object */
    m_graphics = new Graphics();

    // Create textures
    m_graphics->createTexture(":/images/level_easy.png", "level_easy");
    m_graphics->createTexture(":/images/level_hard.png", "level_hard");
    m_graphics->createTexture(":/images/level_island.png", "level_island");
    m_graphics->createTexture(":/images/plat_instructions.png", "welcome");
    m_graphics->createTexture(":/images/particle_1.jpg", "particle");

    /* Create screen */
    addScreen(dynamic_cast<Screen *>(new PlatformerScreen(this,
                                                          container->width(), container->height(),
                                                          1, m_graphics)));
    addScreen(dynamic_cast<Screen *>(new WelcomeScreen(this,
                                                       container->width(), container->height(), 1)));
}

void PlatformerApplication::mouseMoveEvent(QMouseEvent *event)
{
    /* Re-center cursor */
    QCursor::setPos(m_container->mapToGlobal(QPoint(m_container->width() / 2,
                                                    m_container->height() / 2)));

    Application::mouseMoveEvent(event);
}

void PlatformerApplication::keyPressEvent(QKeyEvent *event)
{
    Application::keyPressEvent(event);
}
