#include "FinalApp.h"

#include "engine/graphics/Graphics.h"

#include "final/GameScreen.h"

FinalApp::FinalApp(QGLWidget *container) :
    Application(container, true, true, true, glm::vec4(0.4, 0.5, 0.9, 1))
{
    /* Setup graphics object */
    m_graphics = new Graphics();

    // Create program
    m_graphics->createProgram(":/shaders/shader.vert", ":/shaders/shader.frag", "default");
    m_graphics->setActiveProgram("default");

    // Create textures
    m_graphics->createTexture(":/images/welcome.jpg", "welcome");

    /* Create screen */
    addScreen(dynamic_cast<Screen *>(new GameScreen(this, 1)));
}

void FinalApp::mouseMoveEvent(QMouseEvent *event)
{
    // Re-center cursor
    QCursor::setPos(m_container->mapToGlobal(QPoint(m_container->width() / 2,
                                                    m_container->height() / 2)));

    Application::mouseMoveEvent(event);
}
