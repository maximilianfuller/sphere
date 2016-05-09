#include "planetshape.h"

PlanetShape::PlanetShape()
{
    glGenBuffers(1,&m_VboID);
    glGenVertexArrays(1,&m_VaoID);
}

PlanetShape::~PlanetShape() {
    glDeleteBuffers(1, &m_VboID);
    glDeleteVertexArrays(1, &m_VaoID);
}

void PlanetShape::setVertexData(GLfloat *data, GLsizeiptr size, int numVertices, int vertsPerStrip) {
    m_numVerts = numVertices;
    m_numVertsPerStrip = vertsPerStrip;

    glBindBuffer(GL_ARRAY_BUFFER,m_VboID);
    glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void PlanetShape::setAttribute(GLuint index, GLint size, GLenum type,GLboolean normalized,
                         GLsizei stride, size_t pointer) {
    glBindVertexArray(m_VaoID);
    glBindBuffer(GL_ARRAY_BUFFER,m_VboID);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index,size,type,normalized,stride,(void*)pointer);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void PlanetShape::draw() {

    glBindVertexArray(m_VaoID);
    for(int i = 0; i < m_numVerts; i+=m_numVertsPerStrip) {
        glDrawArrays(GL_TRIANGLE_STRIP,i,m_numVertsPerStrip);
    }
    glBindVertexArray(0);

}



