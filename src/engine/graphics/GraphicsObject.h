#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include "util/CommonIncludes.h"

#include <QString>
#include <QHash>

class GraphicsObject
{
public:
    GraphicsObject();
    ~GraphicsObject();

    bool hasTexture(QString key);
    void createTexture(QString file, QString key);
    void deleteTexture(QString key);
    void loadTexture(QString key, GLenum glTexture, GLint textureLocation);
    void unloadTexture(GLenum glTexture);

    bool hasProgram(QString key);
    void createProgram(const char *vertexShaderFile, const char *fragmentShaderFile, QString key);
    void deleteProgram(QString key);
    void loadProgram(QString key);

private:
    // Texture Map
    QHash<QString, GLuint *> m_textures;

    // Shader Program Map
    QHash<QString, GLuint> m_programs;
};

#endif // GRAPHICSOBJECT_H
