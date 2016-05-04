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
}

Screen::~Screen()
{
    delete m_camera;
    delete m_world;
    delete m_geometryFramebuffer;
    delete m_lightFramebuffer;
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

    delete m_geometryFramebuffer;
    delete m_lightFramebuffer;

    m_geometryFramebuffer = new Framebuffer(w, h, 3,
                                            internalFormatsObject, formatsObject, typesObject);
    m_lightFramebuffer = new Framebuffer(w, h, 1,
                                         internalFormatsLight, formatsLight, typesLight);
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

    // Set pre pass shader
    graphics->setActiveProgram("pre");

    // Bind geometry framebuffer
    m_geometryFramebuffer->bind();

    // Draw geometry
    m_world->drawGeometry(graphics);

    // Cleanup
    m_geometryFramebuffer->unbind();

    /* Light pass */

    // Set light pass shader
    graphics->setActiveProgram("lights");

    // Bind light framebuffer
    m_lightFramebuffer->bind();

    // Bind g buffer textures
    m_geometryFramebuffer->useTextures();
    graphics->sendTexturePosition("position", 0);
    graphics->sendTexturePosition("normal", 1);
    graphics->sendTexturePosition("colorSpecular", 2);

    // Enable light blending
    graphics->enableBlend();
    graphics->enableStencilTest();

    // Draw lights
    m_world->drawLights(graphics);

    // Cleanup
    graphics->disableStencilTest();
    graphics->disableBlend();

    m_lightFramebuffer->unbind();

    /* Post pass */

    // Set post pass shader
    graphics->setActiveProgram("post");

    // Bind light data textures
    m_lightFramebuffer->useTextures();
    graphics->sendTexturePosition("data", 0);

    // Draw geometry
    m_world->drawGeometry(graphics);

    /* Light geometry pass */

    // Set light geometry shader
    graphics->setActiveProgram("lightGeometry");

    // Bind g buffer position texture for environment blending
    m_geometryFramebuffer->useTextures();
    graphics->sendTexturePosition("position", 0);

    // Send time uniform
    graphics->sendTimeUniform(m_time);

    // Enable alpha blending
    graphics->enableBlendAlpha();

    // Draw light geometry
    m_world->drawLightGeometry(graphics);

    // Cleanup
    graphics->disableBlend();

    /* Particle pass */

    // Set particle shader
    graphics->setActiveProgram("particles");

    // Bind g buffer position texture for environment blending
    m_geometryFramebuffer->useTextures();
    graphics->sendTexturePosition("position", 0);

    // Enable particle blending
    graphics->enableBlend();

    // Draw particles
    m_world->drawParticles(graphics);

    // Cleanup
    graphics->disableBlend();
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
