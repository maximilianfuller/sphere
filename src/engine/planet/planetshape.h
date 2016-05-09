#ifndef PLANETSHAPE_H
#define PLANETSHAPE_H

#include <util/CommonIncludes.h>

class PlanetShape
{

public:
    PlanetShape();
    virtual ~PlanetShape();
    void draw();
    void setVertexData(GLfloat *data, GLsizeiptr size, int numVertices, int vertsPerStrip);
    void setAttribute(GLuint index, GLint size, GLenum type,GLboolean normalized, GLsizei stride, size_t pointer);

private:
    GLuint m_VboID;
    GLuint m_VaoID;
    int m_numVerts;
    int m_numVertsPerStrip;
};

#endif // PLANETSHAPE_H
