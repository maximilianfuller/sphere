#ifndef QUADDATA_H
#define QUADDATA_H

int quadVertexCount = 6;

int quadDataSize = 48 * sizeof(GLfloat);

GLfloat quadVertexBufferData[48] = {
    -.5f,0.f,-.5f, 0.f,1.f,0.f, 0.f,1.f,
    -.5f,0.f,.5f, 0.f,1.f,0.f, 0.f,0.f,
    .5f,0.f,-.5f, 0.f,1.f,0.f, 1.f,1.f,
    .5f,0.f,-.5f, 0.f,1.f,0.f, 1.f,1.f,
    -.5f,0.f,.5f, 0.f,1.f,0.f, 0.f,0.f,
    .5f,0.f,.5f, 0.f,1.f,0.f, 1.f,0.f
};

GLfloat fullscreenQuadVertexBufferData[48] = {
    -1.f,-1.f,0.f, 0.f,1.f,0.f, 0.f,0.f,
    1.f,-1.f,0.f, 0.f,1.f,0.f, 1.f,0.f,
    -1.f,1.f,0.f, 0.f,1.f,0.f, 0.f,1.f,
    1.f,-1.f,0.f, 0.f,1.f,0.f, 1.f,0.f,
    1.f,1.f,0.f, 0.f,1.f,0.f, 1.f,1.f,
    -1.f,1.f,.5f, 0.f,1.f,0.f, 0.f,1.f
};

#endif // QUADDATA_H
