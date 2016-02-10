#include "warmup/WarmupApplication.h"

#include "warmup/GameScreen.h"
#include "warmup/WelcomeScreen.h"

#include <QApplication>
#include <QKeyEvent>

WarmupApplication::WarmupApplication(QGLWidget *container) :
    Application(container)
{
    addScreen(dynamic_cast<Screen *>(new GameScreen(this, 1.f)));
    addScreen(dynamic_cast<Screen *>(new HomeScreen(this, 1.f)));
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
