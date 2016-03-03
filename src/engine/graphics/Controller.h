#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "util/CommonIncludes.h"
#include "engine/graphics/VertexData.h"

#include <QString>
#include <QHash>

namespace Graphics
{

class Controller
{
public:
    Controller();
    virtual ~Controller();

    bool hasTexture(QString key);
    GLuint *getTexture(QString key);
    GLuint *createTexture(QString file, QString key);
    void removeTexture(QString key);
    void loadTexture(QString key, GLenum glTexture);
    void unloadTexture(GLenum glTexture);

    bool hasProgram(QString key);
    GLuint getProgram(QString key);
    GLuint createProgram(const char *vertexShaderFile, const char *fragmentShaderFile,
                         QString key);
    void removeProgram(QString key);
    void setActiveProgram(QString key);
    void loadActiveProgram();
    void unloadProgram();

    void createShape(GLfloat *shapeVertexBufferData, int shapeDataSize,
                     int shapeVertexCount, QString key);
    void createQuad(float startU, float startV, float endU, float endV, QString key);
    void drawShape(QString key);

    void setFrustumPlanes(glm::vec4 frustumNX, glm::vec4 frustumX,
                          glm::vec4 frustumNY, glm::vec4 frustumY,
                          glm::vec4 frustumNZ, glm::vec4 frustumZ);

    void sendColorUniform(glm::vec3 color, QString key);
    void sendModelUniform(glm::mat4x4 model, QString key);
    void sendViewUniform(glm::mat4x4 model, QString key);
    void sendProjectionUniform(glm::mat4x4 model, QString key);
    void sendOpacityUniform(float opacity, QString key);
    void sendUseTextureUniform(int useTexture, QString key);

    // View frustum plane equations
    glm::vec4 frustumPlanes[6];

private:
    /* Textures */
    QHash<QString, GLuint *> m_textures;

    /* Shapes */
    QHash<QString, VertexData *> m_shapes;

    // Quad data
    VertexData m_quad;

    // Cylinder data
    VertexData m_cyl;

    /* Shader programs */
    QHash<QString, GLuint> m_programs;

    GLuint m_activeProgram;
};

}

#endif // CONTROLLER_H
