#ifndef SCREEN_H
#define SCREEN_H

#include "util/CommonIncludes.h"

class Application;
namespace Graphics
{
class Controller;
}
class Camera;
class World;

class Screen
{
public:
    Screen(Application *app, float opacity = 1.f, int width = 0,
           int height = 0);
    virtual ~Screen();

    /* Screen opacity */
    float getOpacity();
    void setOpacity(float opacity);

    /* Game Loop */
    virtual void onResize(int w, int h);
    virtual void onTick(float seconds);
    virtual bool onDraw(float &currentOpacity, Graphics::Controller *graphics);

    /* Events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    Application *m_app;

    Camera *m_camera;
    World *m_world;

    int m_width;
    int m_height;

    float m_opacity;
};

#endif // SCREEN_H
