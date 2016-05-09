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
    void blitDepthBuffer(GLuint dest);

    GLuint fbo;

private:
    GLuint m_depthBuffer;
    GLuint *m_textures;

    int m_numTextures;
    int m_width;
    int m_height;
};

#endif // FRAMEBUFFER_H
