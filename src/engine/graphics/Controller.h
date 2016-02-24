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
    GLuint *loadTexture(QString key, GLenum glTexture);
    void unloadTexture(GLenum glTexture);

    bool hasProgram(QString key);
    GLuint getProgram(QString key);
    GLuint createProgram(const char *vertexShaderFile, const char *fragmentShaderFile,
                         QString key);
    void removeProgram(QString key);
    GLuint loadProgram(QString key);
    void unloadProgram();

    void createShape(GLfloat *shapeVertexBufferData, int shapeDataSize,
                     int shapeVertexCount, QString key);
    void createQuad(float startU, float startV, float endU, float endV, QString key);
    void drawShape(QString key);

    void sendColorUniform(glm::vec3 color, QString key);
    void sendModelUniform(glm::mat4x4 model, QString key);
    void sendViewUniform(glm::mat4x4 model, QString key);
    void sendProjectionUniform(glm::mat4x4 model, QString key);
    void sendOpacityUniform(float opacity, QString key);
    void sendUseTextureUniform(int useTexture, QString key);

private:
    // Texture Map
    QHash<QString, GLuint *> m_textures;

    // Shader Program Map
    QHash<QString, GLuint> m_programs;

    // Shape map
    QHash<QString, VertexData *> m_shapes;

    // Quad data
    VertexData m_quad;

    // Cylinder data
    VertexData m_cyl;
};

}

#endif // CONTROLLER_H
