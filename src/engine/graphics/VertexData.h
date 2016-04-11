#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include "util/CommonIncludes.h"

const GLint POSITION_ATTR = 0;
const GLint NORMAL_ATTR = 1;
const GLint TEXTURE_ATTR = 2;

class VertexData
{
public:
    VertexData();
    virtual ~VertexData();

    void setVertexData(GLfloat *data, GLsizeiptr size, int numVertices);

    void setAttribute(GLuint index, GLint size, GLenum type,
                      GLboolean normalized, GLsizei stride, GLvoid *pointer);

    void draw();

private:
    GLuint m_vao;
    GLuint m_vbo;
    int m_numVertices;
};

#endif // VERTEXDATA_H
