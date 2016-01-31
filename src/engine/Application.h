#ifndef APPLICATION_H
#define APPLICATION_H

#include "util/CommonIncludes.h"
#include "engine/Screen.h"
#include "util/Settings.h"

#include <QStack>

const int FRAMES_TO_AVERAGE = 30;

class Application
{
public:
    Application(QGLWidget *container);
    ~Application();

    /* Screen Management */
    void addScreen(Screen *screen);
    void removeScreen(Screen *screen);

    /* Container Management */
    QGLWidget *getContainer() const;

    /* GL Loop */
    virtual void paint();
    virtual void resize(int w, int h);
    virtual void tick();

    /* Input Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    /* Settings */
    Settings settings;

private:
    // Pointer to QGL container
    QGLWidget *m_container;

    // Stack for screen management
    QStack<Screen *> m_screenStack;

    // TODO: set up graphics object
};

#endif // APPLICATION_H
