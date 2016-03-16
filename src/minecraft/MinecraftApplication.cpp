#include "minecraft/MinecraftApplication.h"

#include "engine/graphics/Controller.h"

#include "minecraft/MinecraftScreen.h"
#include "minecraft/MinecraftWelcomeScreen.h"

#include <QApplication>
#include <QKeyEvent>

MinecraftApplication::MinecraftApplication(QGLWidget *container) :
    Application(container, true, true, true, glm::vec4(0.4, 0.5, 0.9, 1))
{
    /* Setup graphics object */
    m_graphics = new Graphics::Controller();

    m_graphics->createProgram(":/shaders/shader.vert", ":/shaders/shader.frag", "default");
    m_graphics->setActiveProgram("default");

    m_graphics->createTexture(":/images/terrain.png", "atlas");
    m_graphics->createTexture(":/images/welcome.jpg", "welcome");
    m_graphics->loadTexture("welcome", 0);

    /* Create screen */
    addScreen(dynamic_cast<Screen *>(new MinecraftScreen(this)));
    addScreen(dynamic_cast<Screen *>(new MinecraftWelcomeScreen(this)));
}

void MinecraftApplication::mouseMoveEvent(QMouseEvent *event)
{
    // Re-center cursor
    QCursor::setPos(m_container->mapToGlobal(QPoint(m_container->width() / 2,
                                                    m_container->height() / 2)));

    Application::mouseMoveEvent(event);
}

void MinecraftApplication::keyPressEvent(QKeyEvent *event)
{
    Application::keyPressEvent(event);
}
