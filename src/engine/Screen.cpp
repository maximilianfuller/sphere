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
    m_time(0),
    m_width(width),
    m_height(height),
    m_camera(NULL),
    m_world(NULL)
{
    m_geometryFramebuffer = NULL;
    m_lightFramebuffer = NULL;
    m_psFramebuffer = NULL;
}

Screen::~Screen()
{
    delete m_camera;
    delete m_world;
    delete m_geometryFramebuffer;
    delete m_lightFramebuffer;
    delete m_psFramebuffer;
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
    GLint internalFormatsObject[3] = {GL_RGBA32F, GL_RGB32F, GL_RGBA};
    GLenum formatsObject[3] = {GL_RGBA, GL_RGBA, GL_RGBA};
    GLenum typesObject[3] = {GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

    /*
    GLint internalFormatsObject[3] = {GL_RGBA32F, GL_RGB32F, GL_RGBA};
    GLenum formatsObject[3] = {GL_RGBA, GL_RGBA, GL_RGBA};
    GLenum typesObject[3] = {GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

    GLint internalFormatsLight[1] = {GL_RGBA32F};
    GLenum formatsLight[1] = {GL_RGBA};
    GLenum typesLight[1] = {GL_FLOAT};
    */

    GLint internalFormatsPs[1] = {GL_RGBA};
    GLenum formatsPs[1] = {GL_RGBA};
    GLenum typesPs[1] = {GL_UNSIGNED_BYTE};

    delete m_geometryFramebuffer;
    delete m_lightFramebuffer;

    /*
    m_geometryFramebuffer = new Framebuffer(w, h, 3,
                                            internalFormatsObject, formatsObject, typesObject);
    m_lightFramebuffer = new Framebuffer(w, h, 1,
                                         internalFormatsLight, formatsLight, typesLight);
                                         */
    m_geometryFramebuffer = new Framebuffer(w, h, 3,
                                            internalFormatsObject, formatsObject, typesObject);
    m_lightFramebuffer = new Framebuffer(w, h, 1,
                                         internalFormatsPs, formatsPs, typesPs);
    m_psFramebuffer = new Framebuffer(w, h, 1,
                                      internalFormatsPs, formatsPs, typesPs);
}

void Screen::onTick(float seconds)
{
    m_time += M_PI / 100;

    if(m_time > M_PI * 2)
    {
        m_time = 0;
    }

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
    m_geometryFramebuffer->bind();

    m_world->drawGeometry(graphics);

    m_geometryFramebuffer->unbind();

    /* Light pass */
    graphics->setActiveProgram("lights");
    m_lightFramebuffer->bind();

    m_geometryFramebuffer->useTextures();
    graphics->sendTexturePosition("position", 0);
    graphics->sendTexturePosition("normal", 1);
    graphics->sendTexturePosition("colorSpecular", 2);

    graphics->enableBlend();
    graphics->enableStencilTest();

    m_world->drawLights(graphics);

    graphics->disableStencilTest();
    graphics->disableBlend();

    m_lightFramebuffer->unbind();

    /* Post pass */
    graphics->setActiveProgram("post");
    m_psFramebuffer->bind();

    m_lightFramebuffer->useTextures();
    graphics->sendTexturePosition("data", 0);

    graphics->sendEmptyMatrices();
    graphics->drawShape("fullscreenQuad");

    /* Light geometry pass */
    graphics->setActiveProgram("lightGeometry");
    m_geometryFramebuffer->blitDepthBuffer(m_psFramebuffer->fbo);

    m_geometryFramebuffer->useTextures();
    graphics->sendTexturePosition("position", 0);
    graphics->sendTimeUniform(m_time);

    graphics->enableBlendAlpha();

    m_world->drawLightGeometry(graphics);

    graphics->disableBlend();

    /* Particle pass */
    graphics->setActiveProgram("particles");

    m_geometryFramebuffer->useTextures();
    graphics->sendTexturePosition("position", 0);

    graphics->enableBlend();

    m_world->drawParticles(graphics);

    graphics->disableBlend();

    m_psFramebuffer->unbind();

    /* Last pass */
    graphics->setActiveProgram("post");

    m_psFramebuffer->useTextures();
    graphics->sendTexturePosition("data", 0);

    graphics->sendEmptyMatrices();
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
