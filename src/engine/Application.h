#ifndef APPLICATION_H
#define APPLICATION_H

#include "util/CommonIncludes.h"

#include <QStack>

class Screen;
class Graphics;

class Application
{
public:
    Application(QGLWidget *container, bool depthTest = true,
                bool cullBack = true, bool ccw = true,
                glm::vec4 clearColor = glm::vec4(0, 0, 0, 0));
    virtual ~Application();

    /* Graphics Controller */
    Graphics *getGraphics();

    /* Screen Management */
    Screen *getScreen(int index);
    void addScreen(Screen *screen);
    void removeScreen(Screen *screen);
    void moveScreen(Screen *screen, int index);

    /* Container Management */
    QGLWidget *getContainer() const;

    /* GL Loop */
    virtual void onResize(int w, int h);
    virtual void onTick(float seconds);
    virtual void onDraw();

    /* Input Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    /* Pointer to QGL container */
    QGLWidget *m_container;

    /* Stack for screen management */
    QStack<Screen *> m_screenStack;

    Graphics *m_graphics;

private:
    glm::vec4 m_clearColor;
};

#endif // APPLICATION_H
