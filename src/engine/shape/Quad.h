#ifndef QUAD_H
#define QUAD_H

#include "engine/shape/Shape.h"
#include "engine/graphics/VertexData.h"

#include <QString>

class Graphics;

class Quad : public Shape
{
public:
    Quad(bool useTexture = false, bool useLighting = true, QString key = "",
         glm::vec4 color = glm::vec4(1, 1, 1, 1),
         glm::vec3 pos = glm::vec3(0, 0, 0),
         glm::vec3 dims = glm::vec3(1, 1, 1));
    virtual ~Quad();

    void draw(Graphics *graphics);

private:
    bool m_useTexture;
    bool m_useLighting;
    QString m_textureKey;
};

#endif // QUAD_H
