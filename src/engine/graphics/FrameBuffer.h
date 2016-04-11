#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "util/CommonIncludes.h"

class Framebuffer
{
public:
    Framebuffer(int width, int height, int numTextures, GLint *internalFormats,
                GLenum *formats, GLenum *types);
    ~Framebuffer();

    void bind();
    void unbind();
    void useTextures();

private:
    GLuint m_fbo;
    GLuint m_depthBuffer;
    GLuint *m_textures;

    int m_numTextures;
};

#endif // FRAMEBUFFER_H
