#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "util/CommonIncludes.h"
#include "engine/graphics/VertexData.h"

#include <QString>
#include <QHash>

class AABoundingBox;

class Graphics
{
public:
    Graphics();
    virtual ~Graphics();

    bool hasTexture(QString key);
    GLuint *getTexture(QString key);
    GLuint *createTexture(QString file, QString key);
    void removeTexture(QString key);
    void loadTexture(QString key, int i);
    void unloadTexture(int i);

    bool hasProgram(QString key);
    GLuint getProgram(QString key);
    GLuint createProgram(const char *vertexShaderFile, const char *fragmentShaderFile,
                         QString key);
    void removeProgram(QString key);
    GLuint getActiveProgram();
    void setActiveProgram(QString key);
    void unloadProgram();

    bool hasShape(QString key);
    void createShape(GLfloat *shapeVertexBufferData, int shapeDataSize,
                     int shapeVertexCount, QString key);
    void createQuad(float startU, float startV, float endU, float endV, QString key);
    void drawShape(QString key);

    void setFrustumPlanes(glm::vec4 frustumNX, glm::vec4 frustumX,
                          glm::vec4 frustumNY, glm::vec4 frustumY,
                          glm::vec4 frustumNZ, glm::vec4 frustumZ);
    bool inFrustum(AABoundingBox *aabb);

    void sendColorUniform(glm::vec4 color);
    void sendIntensityUniform(glm::vec3 intensity);
    void sendAttenuationUniform(glm::vec3 att);
    void sendLightPositionUniform(glm::vec3 pos);
    void sendOpacityUniform(float opacity);
    void sendUseTextureUniform(int useTexture);
    void sendUseLightingUniform(int useLighting);
    void sendTexturePosition(char *textureName, int i);

    void sendModelUniform(glm::mat4x4 model);
    void sendViewUniform(glm::mat4x4 model);
    void sendProjectionUniform(glm::mat4x4 model);

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

    // View frustum plane equations
    glm::vec4 m_frustumPlanes[6];
};

#endif // CONTROLLER_H
