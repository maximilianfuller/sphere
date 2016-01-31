#include "util/CommonIncludes.h"
#include "engine/Application.h"

#include <QApplication>
#include <QKeyEvent>

Application::Application(QGLWidget *container) :
    m_container(container)
{
}

Application::~Application()
{
}

void Application::addScreen(Screen *screen)
{
    m_screenStack.push(screen);
}

/* TODO: send user error if screen not in stack */
void Application::removeScreen(Screen *screen)
{
    // Find screen
    QStack<Screen *>::iterator s;
    int i = 0;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        if(*s == screen)
            break;

        i++;
    }

    // Remove screen
    m_screenStack.remove(i);
}

QGLWidget *Application::getContainer() const
{
    return m_container;
}

void Application::paint()
{
    // Send paint events to screen stack
    QStack<Screen *>::iterator s;
    float currentOpacity = 0.f;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        if(!(*s)->paint(currentOpacity))
        {
            break;
        }
    }
}

void Application::resize(int w, int h)
{
    // Send resize events to screen stack
    QStack<Screen *>::iterator s;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        (*s)->resize(w, h);
    }
}

void Application::tick()
{
    // Tick top of screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->tick();
    }
}

void Application::mousePressEvent(QMouseEvent *event)
{
    // Send event to top of the screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->mousePressEvent(event);
    }
}

void Application::mouseMoveEvent(QMouseEvent *event)
{
    // Re-center mouse
    QCursor::setPos(m_container->mapToGlobal(QPoint(m_container->width() / 2,
                                                    m_container->height() / 2)));

    // Send event to top of the screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->mouseMoveEvent(event);
    }
}

void Application::mouseReleaseEvent(QMouseEvent *event)
{
    // Send event to top of the screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->mouseReleaseEvent(event);
    }
}

void Application::wheelEvent(QWheelEvent *event)
{
    // Send event to top of the screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->wheelEvent(event);
    }
}

void Application::keyPressEvent(QKeyEvent *event)
{
    // Quit
    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }

    // Send event to top of the screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->keyPressEvent(event);
    }
}

void Application::keyReleaseEvent(QKeyEvent *event)
{
    // Send event to top of the screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->keyReleaseEvent(event);
    }
}
