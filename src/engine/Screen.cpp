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
    GLint internalFormatsObject[3] = {GL_RGB16F, GL_RGB16F, GL_RGBA};
    GLenum formatsObject[3] = {GL_RGB, GL_RGB, GL_RGBA};
    GLenum typesObject[3] = {GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

    GLint internalFormatsLight[1] = {GL_RGBA};
    GLenum formatsLight[1] = {GL_RGBA};
    GLenum typesLight[1] = {GL_UNSIGNED_BYTE};

    m_objectDataFBO = new Framebuffer(width, height, 3,
                                      internalFormatsObject, formatsObject, typesObject);
    m_lightDataFBO = new Framebuffer(width, height, 1,
                                     internalFormatsLight, formatsLight, typesLight);
}

Screen::~Screen()
{
    delete m_camera;
    delete m_world;
    delete m_objectDataFBO;
    delete m_lightDataFBO;
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

    /* Remake framebuffers */
    GLint internalFormatsObject[3] = {GL_RGB16F, GL_RGB16F, GL_RGBA};
    GLenum formatsObject[3] = {GL_RGB, GL_RGB, GL_RGBA};
    GLenum typesObject[3] = {GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

    GLint internalFormatsLight[1] = {GL_RGBA};
    GLenum formatsLight[1] = {GL_RGBA};
    GLenum typesLight[1] = {GL_UNSIGNED_BYTE};

    delete m_objectDataFBO;
    delete m_lightDataFBO;

    m_objectDataFBO = new Framebuffer(w, h, 3,
                                      internalFormatsObject, formatsObject, typesObject);
    m_lightDataFBO = new Framebuffer(w, h, 1,
                                     internalFormatsLight, formatsLight, typesLight);
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

void Screen::drawDeferred(Graphics *graphics)
{
    /* Object data pass */
    graphics->setActiveProgram("pre");

    m_objectDataFBO->bind();
    m_world->drawGeometry(graphics);
    m_objectDataFBO->unbind();

    /* Light pass */
    graphics->setActiveProgram("lights");

    m_objectDataFBO->useTextures();
    graphics->sendTexturePosition("position", 0);
    graphics->sendTexturePosition("normal", 1);
    graphics->sendTexturePosition("colorSpecular", 2);

    m_lightDataFBO->bind();
    graphics->enableBlend();
    m_world->drawLights(graphics);
    m_lightDataFBO->unbind();

    /* Final pass */
    graphics->setActiveProgram("post");

    m_lightDataFBO->useTextures();
    graphics->sendTexturePosition("data", 0);

    graphics->disableBlend();
    graphics->sendEmptyMatrices();
    m_camera->setResolution(graphics);
    graphics->drawShape("fullscreenQuad");
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
