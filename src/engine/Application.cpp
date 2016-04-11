#include "engine/Application.h"

#include "engine/Screen.h"
#include "engine/graphics/Graphics.h"

#include <QApplication>
#include <QKeyEvent>

Application::Application(QGLWidget *container, bool depthTest,
                         bool cullBack, bool ccw, glm::vec4 clearColor) :
    m_container(container),
    m_clearColor(clearColor),
    m_graphics(NULL)
{
    if(depthTest)
    {
        glEnable(GL_DEPTH_TEST);
    }

    if(cullBack)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if(ccw)
    {
        glFrontFace(GL_CCW);
    }

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Application::~Application()
{
    delete m_graphics;

    QStack<Screen *>::iterator s;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        delete (*s);
    }
}

Graphics *Application::getGraphics()
{
    return m_graphics;
}

Screen *Application::getScreen(int index)
{
    return m_screenStack[index];
}

void Application::addScreen(Screen *screen)
{
    m_screenStack.push(screen);
}

void Application::removeScreen(Screen *screen)
{
    /* Find screen */
    QStack<Screen *>::iterator s;
    int i = 0;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        if(*s == screen)
            break;

        i++;
    }

    /* Remove screen */
    delete m_screenStack[i];
    m_screenStack.remove(i);
}

void Application::moveScreen(Screen *screen, int index)
{
    /* Find screen */
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

void Application::onDraw()
{
    /* Set clear color */
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);

    /* Clear the color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /* Send paint events to screen stack */
    float currentOpacity = 0.f;

    for(int i = m_screenStack.length() - 1; i >= 0; i--)
    {
        if(!m_screenStack[i]->onDraw(currentOpacity, m_graphics))
        {
            break;
        }
    }
}

void Application::onResize(int w, int h)
{
    /* Send resize events to screen stack */
    QStack<Screen *>::iterator s;

    for(s = m_screenStack.begin(); s != m_screenStack.end(); s++)
    {
        (*s)->onResize(w, h);
    }
}

void Application::onTick(float seconds)
{
    /* Tick top of screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->onTick(seconds);
    }
}

void Application::mousePressEvent(QMouseEvent *event)
{
    /* Send event to top of the screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->mousePressEvent(event);
    }
}

void Application::mouseMoveEvent(QMouseEvent *event)
{
    /* Send event to top of the screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->mouseMoveEvent(event);
    }
}

void Application::mouseReleaseEvent(QMouseEvent *event)
{
    /* Send event to top of the screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->mouseReleaseEvent(event);
    }
}

void Application::wheelEvent(QWheelEvent *event)
{
    /* Send event to top of the screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->wheelEvent(event);
    }
}

void Application::keyPressEvent(QKeyEvent *event)
{
    /* Send event to top of the screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->keyPressEvent(event);
    }
}

void Application::keyReleaseEvent(QKeyEvent *event)
{
    /* Send event to top of the screen stack */
    if(!m_screenStack.isEmpty())
    {
        Screen *top = m_screenStack.top();
        top->keyReleaseEvent(event);
    }
}
