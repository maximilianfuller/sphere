#ifndef SHAPE_H
#define SHAPE_H

#include "util/CommonIncludes.h"

/* Essentially a wrapper for VAO and VBO */
class Shape
{
public:
    Shape();
    virtual ~Shape();

    void setVertexData(GLfloat *data, GLsizeiptr size, int numVertices);

    void setAttribute(GLuint index, GLint size, GLenum type,
                      GLboolean normalized, GLsizei stride, GLvoid *pointer);

    void draw();

private:
    GLuint m_vao;
    GLuint m_vbo;
    int m_numVertices;
};

#endif // SHAPE_H
