#ifndef APPLICATION_H
#define APPLICATION_H

#include "util/CommonIncludes.h"

#include <QStack>

class Settings;
class Screen;

class Application
{
public:
    Application(QGLWidget *container);
    virtual ~Application();

    /* Screen Management */
    Screen *getScreen(int index);
    void addScreen(Screen *screen);
    void removeScreen(Screen *screen);
    void moveScreen(Screen *screen, int index);

    /* Container Management */
    QGLWidget *getContainer() const;

    /* GL Loop */
    virtual void paint();
    virtual void resize(int w, int h);
    virtual void tick(float seconds);

    /* Input Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Settings */
    Settings *settings;

protected:
    // Pointer to QGL container
    QGLWidget *m_container;

    // Stack for screen management
    QStack<Screen *> m_screenStack;
};

#endif // APPLICATION_H
