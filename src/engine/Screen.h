#ifndef SCREEN_H
#define SCREEN_H

#include "util/CommonIncludes.h"
#include "engine/camera/Camera.h"

#include <qgl.h>

class Application;

class Screen
{
public:
    Screen(Application *app, float opacity);
    ~Screen();

    /* Screen opacity */
    float getOpacity();
    void setOpacity(float opacity);

    /* Game Loop */
    virtual bool paint(float &currentOpacity);
    virtual void resize(int w, int h);
    virtual void tick();

    /* Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    // Pointer to QGL container
    Application *m_app;

    // Camera used to render contents of screen
    Camera *m_camera;

    // Screen opacity
    float m_opacity;

    // TODO: add graphics object
    // TODO: add more scene information
};

#endif // SCREEN_H
