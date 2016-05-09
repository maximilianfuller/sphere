#include "tileshape.h"


TileShape::TileShape(int width) : PlanetShape()
{
    int vertexCount = 2*(width+1)*width;
    int vertsPerStrip = 2*(width+1);
    int size = vertexCount*5*sizeof(GLfloat);

    GLfloat *vertexBufferData = new GLfloat[size];
    int index = 0;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < width+1; j++) {
            vertexBufferData[index] = j; index++;
            vertexBufferData[index] = 0.f; index++;
            vertexBufferData[index] = i; index++;
            vertexBufferData[index] = ((float)j)/width; index++;
            vertexBufferData[index] = ((float)i)/width; index++;
            vertexBufferData[index] = j; index++;
            vertexBufferData[index] = 0.f; index++;
            vertexBufferData[index] = i+1; index++;
            vertexBufferData[index] = ((float)j)/width; index++;
            vertexBufferData[index] = (float)(i+1)/width; index++;

        }
    }

    setVertexData(vertexBufferData, size, vertexCount, vertsPerStrip);
    setAttribute(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5, 0);
    setAttribute(1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5, 3*sizeof(GLfloat));
}
