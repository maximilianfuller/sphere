#include "engine/graphics/Graphics.h"

#include "util/ResourceLoader.h"
#include "util/QuadData.h"
#include "util/CylinderData.h"
#include "util/SphereData.h"

#include "engine/intersect/AABoundingBox.h"

#include <QImage>
#include <QGLWidget>

Graphics::Graphics()
{
    /* Default Shapes */
    createShape(quadVertexBufferData, quadDataSize, quadVertexCount, "quad");
    createShape(fullscreenQuadVertexBufferData, quadDataSize, quadVertexCount,
                "fullscreenQuad");
    createShape(cylinderVertexBufferData, cylinderDataSize, cylinderVertexCount,
                "cylinder");
    createShape(sphereVertexBufferData, sphereDataSize, sphereVertexCount,
                "sphere");

    /* Default Shaders */
    createProgram(":/shaders/shader.vert", ":/shaders/particles.frag", "particles");
    createProgram(":/shaders/shader.vert", ":/shaders/combine.frag", "combine");
    createProgram(":/shaders/shader.vert", ":/shaders/pre.frag", "pre");
    createProgram(":/shaders/shader.vert", ":/shaders/lights.frag", "lights");
    createProgram(":/shaders/shader.vert", ":/shaders/post.frag", "post");
    createProgram(":/shaders/shader.vert", ":/shaders/lightGeometry.frag", "lightGeometry");
}

Graphics::~Graphics()
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

bool Graphics::hasTexture(QString key)
{
    return m_textures.contains(key);
}

GLuint *Graphics::getTexture(QString key)
{
    return m_textures.value(key);
}

GLuint *Graphics::createTexture(QString file, QString key)
{
    /* Open image file */
    QImage image(file);
    image = QGLWidget::convertToGLFormat(image);

    /* Generate texture */
    GLuint *texture = new GLuint;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glBindTexture(GL_TEXTURE_2D, 0);

    /* Add texture to hash table */
    m_textures.insert(key, texture);

    return texture;
}

void Graphics::removeTexture(QString key)
{
    GLuint *texture = m_textures.value(key);
    glDeleteTextures(1, texture);
    delete texture;

    m_textures.remove(key);
}

void Graphics::loadTexture(QString key, int i)
{
    /* Get texture from map */
    GLuint *texture = m_textures.value(key, 0);

    /* Bind texture */
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, *texture);
}

void Graphics::unloadTexture(int i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Graphics::hasProgram(QString key)
{
    return m_programs.contains(key);
}

GLuint Graphics::getProgram(QString key)
{
    return m_programs.value(key);
}

GLuint Graphics::createProgram(const char *vertexShaderFile, const char *fragmentShaderFile, QString key)
{
    /* Load program from shaders */
    GLuint program;
    program = ResourceLoader::loadShaders(vertexShaderFile, fragmentShaderFile);

    /* Insert program into hash table */
    m_programs.insert(key, program);

    return program;
}

void Graphics::removeProgram(QString key)
{
    GLuint program = m_programs.value(key, -1);
    glDeleteProgram(program);

    m_programs.remove(key);
}


GLuint Graphics::getActiveProgram()
{
    return m_activeProgram;
}

void Graphics::setActiveProgram(QString key)
{
    GLuint program = m_programs.value(key, -1);
    m_activeProgram = program;
    glUseProgram(m_activeProgram);
}

void Graphics::unloadProgram()
{
    glUseProgram(0);
}

bool Graphics::hasShape(QString key)
{
    return m_shapes.contains(key);
}

void Graphics::createShape(GLfloat *shapeVertexBufferData,
                             int shapeDataSize, int shapeVertexCount,
                             QString key)
{
    VertexData *data = new VertexData();

    data->setVertexData(shapeVertexBufferData, shapeDataSize, shapeVertexCount);
    data->setAttribute(POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) 0);
    data->setAttribute(NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    data->setAttribute(TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    m_shapes.insert(key, data);
}

void Graphics::createQuad(float startU, float startV, float endU, float endV,
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
    data->setAttribute(POSITION_ATTR, 3, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) 0);
    data->setAttribute(NORMAL_ATTR, 3, GL_FLOAT, GL_TRUE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 3));
    data->setAttribute(TEXTURE_ATTR, 2, GL_FLOAT, GL_FALSE,
                       sizeof(GLfloat) * 8, (void *) (sizeof(GLfloat) * 6));

    m_shapes.insert(key, data);
}

void Graphics::drawShape(QString key)
{
    m_shapes.value(key)->draw();
}

void Graphics::setFrustumPlanes(glm::vec4 fnx, glm::vec4 fx,
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

bool Graphics::inFrustum(AABoundingBox *aabb)
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

void Graphics::enableBlend()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glDisable(GL_CULL_FACE);

    glDepthMask(GL_FALSE);
}

void Graphics::enableBlendAlpha()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_FALSE);
}

void Graphics::disableBlend()
{
    glDisable(GL_BLEND);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glDepthMask(GL_TRUE);
}

void Graphics::enableStencilTest()
{
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
}

void Graphics::disableStencilTest()
{
    glDisable(GL_STENCIL_TEST);
}

void Graphics::setStencilId(int id)
{
    glStencilFunc(GL_NOTEQUAL, id, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF);
}

void Graphics::sendTimeUniform(float time)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "time"), time);
}

void Graphics::sendResolutionUniform(glm::vec2 res)
{
    glUniform2fv(glGetUniformLocation(m_activeProgram, "res"), 1,
                 glm::value_ptr(res));
}

void Graphics::sendColorUniform(glm::vec4 color)
{
    glUniform4fv(glGetUniformLocation(m_activeProgram, "color"), 1,
                 glm::value_ptr(color));
}

void Graphics::sendShininessUniform(float shininess)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "shininess"), shininess);
}


void Graphics::sendLightTypeUniform(int lightType)
{
    glUniform1i(glGetUniformLocation(m_activeProgram, "lightType"), lightType);
}

void Graphics::sendIntensityUniform(glm::vec3 intensity)
{
    glUniform3fv(glGetUniformLocation(m_activeProgram, "lightInt"), 1,
                 glm::value_ptr(intensity));
}

void Graphics::sendAmbientCoefficient(float coeff)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "ambCoeff"), coeff);
}

void Graphics::sendDiffuseCoefficient(float coeff)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "diffCoeff"), coeff);
}

void Graphics::sendSpecularCoefficient(float coeff)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "specCoeff"), coeff);
}

void Graphics::sendAttenuationUniform(glm::vec3 att)
{
    glUniform3fv(glGetUniformLocation(m_activeProgram, "lightAtt"), 1,
                 glm::value_ptr(att));
}

void Graphics::sendLightRadiusUniform(float radius)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "lightRadius"), radius);
}

void Graphics::sendLightPositionUniform(glm::vec3 pos)
{
    glUniform3fv(glGetUniformLocation(m_activeProgram, "lightPos"), 1,
                 glm::value_ptr(pos));
}

void Graphics::sendLightDirectionUniform(glm::vec3 dir)
{
    glUniform3fv(glGetUniformLocation(m_activeProgram, "lightDir"), 1,
                 glm::value_ptr(dir));
}

void Graphics::sendParticleAgeUniform(float age)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "age"), age);
}

void Graphics::sendOpacityUniform(float opacity)
{
    glUniform1f(glGetUniformLocation(m_activeProgram, "opacity"), opacity);
}

void Graphics::sendUseTextureUniform(int useTexture)
{
    glUniform1i(glGetUniformLocation(m_activeProgram, "useTexture"),
                useTexture);
}

void Graphics::sendUseLightingUniform(int useLighting)
{
    glUniform1i(glGetUniformLocation(m_activeProgram, "useLighting"),
                useLighting);
}

void Graphics::sendTexturePosition(char *textureName, int i)
{
    glUniform1i(glGetUniformLocation(m_activeProgram, textureName),
                i);
}

void Graphics::sendModelUniform(glm::mat4x4 model)
{
    glUniformMatrix4fv(glGetUniformLocation(m_activeProgram, "m"), 1, GL_FALSE,
                       glm::value_ptr(model));
}

void Graphics::sendViewUniform(glm::mat4x4 view)
{
    glUniformMatrix4fv(glGetUniformLocation(m_activeProgram, "v"), 1, GL_FALSE,
                       glm::value_ptr(view));
}

void Graphics::sendProjectionUniform(glm::mat4x4 proj)
{
    glUniformMatrix4fv(glGetUniformLocation(m_activeProgram, "p"), 1, GL_FALSE,
                       glm::value_ptr(proj));
}

void Graphics::sendEmptyMatrices()
{
    sendModelUniform(glm::mat4x4());
    sendViewUniform(glm::mat4x4());
    sendProjectionUniform(glm::mat4x4());
}
