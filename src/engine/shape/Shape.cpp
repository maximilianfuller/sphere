#include "Shape.h"

Shape::Shape()
{
    // Generate vao and vbo
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void Shape::setVertexData(GLfloat *data, GLsizeiptr size, int numVertices)
{
    // Set the number of vertices
    m_numVertices = numVertices;

    // Send vertex data to GPU
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Shape::setAttribute(GLuint index, GLint size, GLenum type,
                         GLboolean normalized, GLsizei stride, GLvoid *pointer)
{
    // Enable and describe vertex attribute
    glBindVertexArray(m_vao);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);

    glBindVertexArray(0);
}

void Shape::draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
    glBindVertexArray(0);
}
