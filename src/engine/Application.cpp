#include "engine/Application.h"

#include "util/Settings.h"

#include "engine/Screen.h"

#include <QApplication>
#include <QKeyEvent>

Application::Application(QGLWidget *container) :
    m_container(container)
{
}

Application::~Application()
{
    QStack<Screen *>::iterator s;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        delete (*s);
    }
}

Screen *Application::getScreen(int index)
{
    return m_screenStack[index];
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
    delete m_screenStack[i];
    m_screenStack.remove(i);
}

void Application::moveScreen(Screen *screen, int index)
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

    m_screenStack.remove(i);
    m_screenStack.insert(index, *s);
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

    for(int i = m_screenStack.length() - 1; i >= 0; i--)
    {
        if(!m_screenStack[i]->paint(currentOpacity))
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

void Application::tick(float seconds)
{
    // Tick top of screen stack
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->tick(seconds);
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
