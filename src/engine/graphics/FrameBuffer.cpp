#include "FrameBuffer.h"

Framebuffer::Framebuffer(int width, int height, int numTextures,
                         GLint *internalFormats, GLenum *formats, GLenum *types) :
    m_textures(new GLuint[numTextures]),
    m_numTextures(numTextures)
{
    /* Generate OGL objects */
    glGenFramebuffers(1, &m_fbo);
    glGenTextures(numTextures, m_textures);
    glGenRenderbuffers(1, &m_depthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);

    /* Allocate textures */
    for(int i = 0; i < numTextures; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormats[i], width, height, 0,
                     formats[i], types[i], NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D,
                             m_textures[i], 0);
    }

    /* Allocate depth buffer */
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(m_numTextures, m_textures);
    glDeleteRenderbuffers(1, &m_depthBuffer);

    delete m_textures;
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// NOTE: may have to find a way to bind more specifically
void Framebuffer::useTextures()
{
    /*
    for(int i = 0; i < m_numTextures; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
    }
    */

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textures[0]);
}
