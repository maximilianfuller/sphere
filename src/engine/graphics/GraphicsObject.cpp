#include "GraphicsObject.h"
#include "util/ResourceLoader.h"

#include <QImage>
#include <QGLWidget>

GraphicsObject::GraphicsObject()
{
}

GraphicsObject::~GraphicsObject()
{
    // Delete textures
    QHash<QString, GLuint *>::iterator t;

    for(t = m_textures.begin(); t != m_textures.end(); t++)
    {
        glDeleteTextures(1, *t);
    }

    // Delete programs
    QHash<QString, GLuint>::iterator p;

    for(p = m_programs.begin(); p != m_programs.end(); p++)
    {
        glDeleteProgram(*p);
    }
}

bool GraphicsObject::hasTexture(QString key)
{
    return m_textures.contains(key);
}

/* TODO: error if texture exists */
void GraphicsObject::createTexture(QString file, QString key)
{
    // Open image file
    QImage image(file);
    image = QGLWidget::convertToGLFormat(image);

    // Generate texture
    GLuint *texture;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glBindTexture(GL_TEXTURE_2D, 0);

    // Add texture to table
    m_textures.insert(key, texture);
}

/* TODO: error if texture doesn't exist */
void GraphicsObject::deleteTexture(QString key)
{
    GLuint *texture = m_textures.value(key);
    glDeleteTextures(1, texture);

    m_textures.remove(key);
}

/* TODO: error if texture doesn't exist */
void GraphicsObject::loadTexture(QString key, GLenum glTexture, GLint textureLocation)
{
    // Get texture from map
    GLuint *texture = m_textures.value(key, 0);

    // Set texture uniform
    glUniform1i(textureLocation, glTexture);

    // Bind texture
    glActiveTexture(glTexture);
    glBindTexture(GL_TEXTURE_2D, *texture);
}

void GraphicsObject::unloadTexture(GLenum glTexture)
{
    glActiveTexture(glTexture);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool GraphicsObject::hasProgram(QString key)
{
    return m_textures.contains(key);
}

/* TODO: error if program exists */
void GraphicsObject::createProgram(const char *vertexShaderFile, const char *fragmentShaderFile, QString key)
{
    // Load program from shaders
    GLuint program;
    program = ResourceLoader::loadShaders(vertexShaderFile, fragmentShaderFile);

    // Insert program
    m_programs.insert(key, program);
}

/* TODO: error if program doesn't exist */
void GraphicsObject::deleteProgram(QString key)
{
    GLuint program = m_programs.value(key, -1);
    glDeleteProgram(program);

    m_programs.remove(key);
}

/* TODO: error if program doesn't exist */
void GraphicsObject::loadProgram(QString key)
{
    GLuint program = m_programs.value(key, -1);
    glUseProgram(program);
}
