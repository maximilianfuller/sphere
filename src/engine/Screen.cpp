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
    GLint internalFormatsObject[2] = {GL_RGB16F, GL_RGB16F};
    GLenum formatsObject[2] = {GL_RGB, GL_RGB};
    GLenum typesObject[2] = {GL_FLOAT, GL_FLOAT};

    GLint internalFormatsLight[2] = {GL_RGBA};
    GLenum formatsLight[2] = {GL_RGBA};
    GLenum typesLight[2] = {GL_UNSIGNED_BYTE};

    m_objectDataFBO = new Framebuffer(800, 600, 2,
                                      internalFormatsObject, formatsObject, typesObject);
    m_lightDataFBO = new Framebuffer(800, 600, 1,
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

/*
 * Calculate attenuation using position and light position
 * Calculate diffuse component using position, light position, normal
 * Calculate specular component using eye position, position, light position
 * Use default coefficients and then send to combine
 * Make third shader which combines lighting (vector for each intensity) and color, by vector product.
 */
void Screen::drawDeferred(Graphics *graphics)
{
    /* Object data pass */
    graphics->setActiveProgram("pre");
    m_camera->setTransforms(graphics);

    m_objectDataFBO->bind();
    m_world->drawGeometry(graphics);
    m_objectDataFBO->unbind();

    /* Light pass */
    graphics->setActiveProgram("lights");
    m_camera->setTransforms(graphics);

    m_objectDataFBO->useTextures();
    graphics->sendTexturePosition("position", 0);
    graphics->sendTexturePosition("normal", 1);

    m_lightDataFBO->bind();

    glDisable(GL_CULL_FACE);

    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_BLEND);

    m_world->drawLights(graphics);
    m_lightDataFBO->unbind();

    /* Final pass */
    glDisable(GL_BLEND);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    graphics->setActiveProgram("post");
    m_camera->setTransforms(graphics);

    m_lightDataFBO->useTextures();
    graphics->sendTexturePosition("data", 0);

    m_world->drawGeometry(graphics);
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
