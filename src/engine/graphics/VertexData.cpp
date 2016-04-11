#include "engine/graphics/VertexData.h"

VertexData::VertexData()
{
    /* Generate vao and vbo */
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
}

VertexData::~VertexData()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void VertexData::setVertexData(GLfloat *data, GLsizeiptr size, int numVertices)
{
    /* Set the number of vertices */
    m_numVertices = numVertices;

    /* Send vertex data to GPU */
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexData::setAttribute(GLuint index, GLint size, GLenum type,
                              GLboolean normalized, GLsizei stride,
                              GLvoid *pointer)
{
    /* Enable and describe vertex attribute */
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexData::draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
    glBindVertexArray(0);
}
