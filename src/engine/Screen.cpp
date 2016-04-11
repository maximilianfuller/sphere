#include "engine/Screen.h"

#include "engine/Application.h"
#include "engine/camera/Camera.h"
#include "engine/world/World.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/FrameBuffer.h"

#include <QKeyEvent>

Screen::Screen(Application *app, float opacity, int width, int height) :
    m_app(app),
    m_opacity(opacity),
    m_width(width),
    m_height(height),
    m_camera(NULL),
    m_world(NULL)
{
    GLint ifObject[3] = {GL_RGB16F, GL_RGB16F, GL_RGBA};
    GLenum fObject[3] = {GL_RGB, GL_RGB, GL_RGBA};
    GLenum tObject[3] = {GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

    GLint ifLight[1] = {GL_RGBA};
    GLenum fLight[1] = {GL_RGBA};
    GLenum tLight[1] = {GL_UNSIGNED_BYTE};

    m_objectDataFBO = new Framebuffer(width, height, 3,
                                      ifObject, fObject, tObject);

    m_lightDataFBO = new Framebuffer(width, height, 1,
                                     ifLight, fLight, tLight);
}

Screen::~Screen()
{
    delete m_camera;
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

void Screen::onResize(int w, int h)
{
    /* Update width and height */
    m_width = w;
    m_height = h;

    /* Update camera */
    glm::vec2 size = glm::vec2(static_cast<float>(w), static_cast<float>(h));
    m_camera->setRatio(size);
}

void Screen::onTick(float seconds)
{
    m_world->onTick(seconds);
}

bool Screen::onDraw(float &currentOpacity, Graphics *graphics)
{
    /* Opacity calculation */
    float maxOpacity = 1.f - currentOpacity;
    bool morePaint = maxOpacity > m_opacity;
    float opacity = morePaint ? m_opacity : maxOpacity;

    currentOpacity += opacity;

    /* Render world */
    drawDeferred(graphics);

    return morePaint;
}

//TODO: make shaders
//TODO: load shaders
//TODO: re-factor uniform sending
//TODO: ensure textures used
void Screen::drawDeferred(Graphics *graphics)
{
    graphics->setActiveProgram("pre");
    m_camera->setTransforms(graphics);

    m_objectDataFBO->bind();
    m_world->drawGeometry(graphics);

    graphics->setActiveProgram("lights");
    m_camera->setTransforms(graphics);

    m_objectDataFBO->unbind();
    m_objectDataFBO->useTextures();
    //m_lightDataFBO->bind();
    //m_world->drawLights(graphics);
    m_world->drawGeometry(graphics);

    /*
    graphics->setActiveProgram("post");
    m_camera->setTransforms(graphics);

    m_lightDataFBO->unbind();
    m_lightDataFBO->useTextures();
    m_world->drawGeometry(graphics);
    */
}

void Screen::mousePressEvent(QMouseEvent *event)
{
    m_world->mousePressEvent(event);
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
    m_world->mouseMoveEvent(event, m_width / 2, m_height / 2);
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
