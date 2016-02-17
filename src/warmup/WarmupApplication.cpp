#include "warmup/WarmupApplication.h"

#include "engine/graphics/Controller.h"

#include "warmup/GameScreen.h"
#include "warmup/WelcomeScreen.h"

#include <QApplication>
#include <QKeyEvent>

WarmupApplication::WarmupApplication(QGLWidget *container) :
    Application(container, true, true, true, glm::vec4(0.4, 0.5, 0.9, 1))
{
    /* Setup graphics object */
    m_graphics = new Graphics::Controller();

    m_graphics->createProgram(":/shaders/shader.vert", ":/shaders/shader.frag", "default");

    m_graphics->createTexture(":/images/grass.png", "grass");
    m_graphics->createTexture(":/images/welcome.jpg", "welcome");

    /* Create screens */
    addScreen(dynamic_cast<Screen *>(new GameScreen(this)));
    addScreen(dynamic_cast<Screen *>(new WelcomeScreen(this)));
}

void WarmupApplication::mouseMoveEvent(QMouseEvent *event)
{
    // Re-center cursor
    QCursor::setPos(m_container->mapToGlobal(QPoint(m_container->width() / 2,
                                                    m_container->height() / 2)));

    Application::mouseMoveEvent(event);
}

void WarmupApplication::keyPressEvent(QKeyEvent *event)
{
    Application::keyPressEvent(event);
}
