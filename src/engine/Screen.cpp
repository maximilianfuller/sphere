#include "engine/Screen.h"
#include "engine/Application.h"

#include <QKeyEvent>

Screen::Screen(Application *app, float opacity) :
    m_app(app),
    m_opacity(opacity)
{
}

Screen::~Screen()
{
    delete m_camera;
}

float Screen::getOpacity()
{
    return m_opacity;
}

void Screen::setOpacity(float opacity)
{
    m_opacity = opacity;
}

bool Screen::paint(float &currentOpacity)
{
    /* Opacity calculation */

    // Max possible opacity
    float maxOpacity = 1.f - currentOpacity;

    // Whether or not more screens can be painted
    bool morePaint = maxOpacity > m_opacity;

    // Choose appropriate opacity
    float opacity = morePaint ? m_opacity : maxOpacity;

    /* TODO: Render scene (use graphics object, scene information, opacity) */

    /* Update opacity and return */
    currentOpacity += opacity;
    return morePaint;
}

void Screen::resize(int w, int h)
{
    // Update camera
    glm::vec2 size = glm::vec2(static_cast<float>(w), static_cast<float>(h));
    m_camera->setRatio(size);
}

void Screen::tick()
{
}

void Screen::mousePressEvent(QMouseEvent *event)
{
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
}

void Screen::mouseReleaseEvent(QMouseEvent *event)
{
}

void Screen::wheelEvent(QWheelEvent *event)
{
}

void Screen::keyPressEvent(QKeyEvent *event)
{
}

void Screen::keyReleaseEvent(QKeyEvent *event)
{
}
