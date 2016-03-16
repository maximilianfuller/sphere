#include "engine/graphics/Controller.h"

#include "util/ResourceLoader.h"
#include "util/QuadData.h"
#include "util/CylinderData.h"

#include "engine/intersect/AABoundingBox.h"

#include <QImage>
#include <QGLWidget>

using namespace Graphics;

Controller::Controller()
{
    createShape(quadVertexBufferData, quadDataSize, quadVertexCount, "quad");
    createShape(fullscreenQuadVertexBufferData, quadDataSize, quadVertexCount,
                "fullscreenQuad");
    createShape(cylinderVertexBufferData, cylinderDataSize, cylinderVertexCount,
                "cylinder");
}

Controller::~Controller()
{
    /* Delete textures */
    QHash<QString, GLuint *>::iterator t;

    for(t = m_textures.begin(); t != m_textures.end(); t++)
    {
        glDeleteTextures(1, *t);
        delete (*t);
    }

    /* Delete programs */
    QHash<QString, GLuint>::iterator p;

    for(p = m_programs.begin(); p != m_programs.end(); p++)
    {
        glDeleteProgram(*p);
    }

    /* Delete shapes */
    QHash<QString, VertexData *>::iterator s;

    for(s = m_shapes.begin(); s != m_shapes.end(); s++)
    {
        delete (*s);
    }
}

bool Controller::hasTexture(QString key)
{
    return m_textures.contains(key);
}

GLuint *Controller::getTexture(QString key)
{
    return m_textures.value(key);
}

GLuint *Controller::createTexture(QString file, QString key)
{
    /* Open image file */
    QImage image(file);
    image = QGLWidget::convertToGLFormat(image);

    /* Generate texture */
    GLuint *texture = new GLuint;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glBindTexture(GL_TEXTURE_2D, 0);

    /* Add texture to hash table */
    m_textures.insert(key, texture);

    return texture;
}

void Controller::removeTexture(QString key)
{
    GLuint *texture = m_textures.value(key);
    glDeleteTextures(1, texture);
    delete texture;

    m_textures.remove(key);
}

void Controller::loadTexture(QString key, int i)
{
    /* Get texture from map */
    GLuint *texture = m_textures.value(key, 0);

    /* Bind texture */
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, *texture);
}

void Controller::unloadTexture(int i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Controller::hasProgram(QString key)
{
    return m_textures.contains(key);
}

GLuint Controller::getProgram(QString key)
{
    return m_programs.value(key);
}

GLuint Controller::createProgram(const char *vertexShaderFile, const char *fragmentShaderFile, QString key)
{
    /* Load program from shaders */
    GLuint program;
    program = ResourceLoader::loadShaders(vertexShaderFile, fragmentShaderFile);

    /* Insert program into hash table */
    m_programs.insert(key, program);

    return program;
}

void Controller::removeProgram(QString key)
{
    GLuint program = m_programs.value(key, -1);
    glDeleteProgram(program);

    m_programs.remove(key);
}

void Controller::setActiveProgram(QString key)
{
    GLuint program = m_programs.value(key, -1);
    m_activeProgram = program;
}

void Controller::loadActiveProgram()
{
    glUseProgram(m_activeProgram);
}

void Controller::unloadProgram()
{
    glUseProgram(0);
}

void Controller::createShape(GLfloat *shapeVertexBufferData,
                             int shapeDataSize, int shapeVertexCount,
                             QString key)
{
    VertexData *data = new VertexData();

    data->setVertexData(shapeVertexBufferData, shapeDataSize, shapeVertexCount);
    data->setAttribute(Graphics::POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) 0);
    data->setAttribute(Graphics::NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    data->setAttribute(Graphics::TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    m_shapes.insert(key, data);
}

void Controller::createQuad(float startU, float startV, float endU, float endV,
                            QString key)
{
    int quadVertexCount = 6;

    int quadDataSize = 48 * sizeof(GLfloat);

    GLfloat quadVertexBufferData[48] = {
        -.5f,0.f,-.5f, 0.f,1.f,0.f, startU,endV,
        -.5f,0.f,.5f, 0.f,1.f,0.f, startU,startV,
        .5f,0.f,-.5f, 0.f,1.f,0.f, endU,endV,
        .5f,0.f,-.5f, 0.f,1.f,0.f, endU,endV,
        -.5f,0.f,.5f, 0.f,1.f,0.f, startU,startV,
        .5f,0.f,.5f, 0.f,1.f,0.f, endU,startV
    };

    VertexData *data = new VertexData();

    data->setVertexData(quadVertexBufferData, quadDataSize, quadVertexCount);
    data->setAttribute(Graphics::POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) 0);
    data->setAttribute(Graphics::NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    data->setAttribute(Graphics::TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    m_shapes.insert(key, data);
}

void Controller::drawShape(QString key)
{
    m_shapes.value(key)->draw();
}

void Controller::setFrustumPlanes(glm::vec4 fnx, glm::vec4 fx,
                                  glm::vec4 fny, glm::vec4 fy,
                                  glm::vec4 fnz, glm::vec4 fz)
{
    m_frustumPlanes[0] = fnx;
    m_frustumPlanes[1] = fx;

    m_frustumPlanes[2] = fny;
    m_frustumPlanes[3] = fy;

    m_frustumPlanes[4] = fnz;
    m_frustumPlanes[5] = fz;
}

bool Controller::inFrustum(AABoundingBox *aabb)
{
    glm::vec3 boxPos = aabb->getPosition();
    glm::vec3 boxDims = aabb->getDimensions();

    for(int i = 0; i < 6; i++)
    {
        bool allBehind = true;

        for(int x = 0; x <= 1; x++)
        {
            for(int y = 0; y <= 1; y++)
            {
                for(int z = 0; z <= 1; z++)
                {
                    glm::vec4 pos = glm::vec4(boxPos.x + x * boxDims.x,
                                              boxPos.y + y * boxDims.y,
                                              boxPos.z + z * boxDims.z, 1);

                    allBehind &= glm::dot(m_frustumPlanes[i], pos) < 0;
                }
            }
        }

        if(allBehind)
        {
            return false;
        }
    }

    return true;
}

void Controller::sendColorUniform(glm::vec4 color, QString key)
{
    glUniform4fv(glGetUniformLocation(getProgram(key), "color"), 1,
                 glm::value_ptr(color));
}

void Controller::sendModelUniform(glm::mat4x4 model, QString key)
{
    glUniformMatrix4fv(glGetUniformLocation(getProgram(key), "m"), 1, GL_FALSE,
                       glm::value_ptr(model));
}

void Controller::sendViewUniform(glm::mat4x4 view, QString key)
{
    glUniformMatrix4fv(glGetUniformLocation(getProgram(key), "v"), 1, GL_FALSE,
                       glm::value_ptr(view));
}

void Controller::sendProjectionUniform(glm::mat4x4 proj, QString key)
{
    glUniformMatrix4fv(glGetUniformLocation(getProgram(key), "p"), 1, GL_FALSE,
                       glm::value_ptr(proj));
}

void Controller::sendOpacityUniform(float opacity, QString key)
{
    glUniform1f(glGetUniformLocation(getProgram(key), "opacity"), opacity);
}

void Controller::sendUseTextureUniform(int useTexture, QString key)
{
    glUniform1i(glGetUniformLocation(getProgram(key), "useTexture"),
                useTexture);
}

void Controller::sendUseLightingUniform(int useLighting, QString key)
{
    glUniform1i(glGetUniformLocation(getProgram(key), "useLighting"),
                useLighting);
}
