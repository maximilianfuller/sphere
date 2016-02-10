#include "engine/Screen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/graphics/Controller.h"
#include "engine/world/World.h"

#include <QKeyEvent>

Screen::Screen(Application *app, float opacity) :
    m_app(app),
    m_opacity(opacity),
    m_graphics(NULL),
    m_camera(NULL),
    m_world(NULL)
{
}

Screen::~Screen()
{
    delete m_camera;
    delete m_graphics;
    delete m_world;
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
    float maxOpacity = 1.f - currentOpacity;
    bool morePaint = maxOpacity > m_opacity;
    float opacity = morePaint ? m_opacity : maxOpacity;

    currentOpacity += opacity;

    /* Render the scene */

    // Load shader program
    m_graphics->loadProgram("default");

    // Send opacity and camera uniforms
    m_graphics->sendOpacityUniform(opacity, "default");
    m_camera->setTransforms(m_graphics);

    // Render world
    m_world->draw(m_graphics);

    // Unload shader program
    m_graphics->unloadProgram();

    return morePaint;
}

void Screen::resize(int w, int h)
{
    // Update camera
    glm::vec2 size = glm::vec2(static_cast<float>(w), static_cast<float>(h));
    m_camera->setRatio(size);
}

void Screen::tick(float seconds)
{
    m_world->tick(seconds);
}

void Screen::mousePressEvent(QMouseEvent *event)
{
    m_world->mousePressEvent(event);
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
    m_world->mouseMoveEvent(event, m_app->getContainer()->width() / 2,
                            m_app->getContainer()->height() / 2);
}

void Screen::mouseReleaseEvent(QMouseEvent *event)
{
    m_world->mouseReleaseEvent(event);
}

void Screen::wheelEvent(QWheelEvent *event)
{
    m_world->wheelEvent(event);
}

void Screen::keyPressEvent(QKeyEvent *event)
{
    m_world->keyPressEvent(event);
}

void Screen::keyReleaseEvent(QKeyEvent *event)
{
    m_world->keyReleaseEvent(event);
}
