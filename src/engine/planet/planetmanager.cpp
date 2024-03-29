#include "planetmanager.h"
#include "tileshape.h"
#include "planetshape.h"
#include "util/ResourceLoader.h"
#include "quadtree.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/FrameBuffer.h"

PlanetManager::PlanetManager(Graphics *graphics)
{
    m_graphics = graphics;
    initializeQuad(QUAD_WIDTH);
    initializeNoiseTexture();


    GLint internalFormats[1] = {GL_RGBA32F};
    GLenum formats[1] = {GL_RGBA};
    GLenum types[1] = {GL_FLOAT};


    m_fb = new Framebuffer(1, 1, 1, internalFormats, formats, types);
}

void PlanetManager::drawPlanet(glm::vec3 eye, glm::vec3 playerLoc) {

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //set uniforms
    GLuint shader = m_graphics->getActiveProgram();
    glUniform1i(glGetUniformLocation(shader, "collisionDetection"), 0);
    loadNoiseTexture(shader);

    //set noise texture

    //draw faces of cube
    drawFace(TOP, eye, playerLoc);
    drawFace(BOTTOM, eye, playerLoc);
    drawFace(LEFT, eye, playerLoc);
    drawFace(RIGHT, eye, playerLoc);
    drawFace(FRONT, eye, playerLoc);
    drawFace(BACK, eye, playerLoc);

}

void PlanetManager::drawFace(int face, glm::vec3 eye, glm::vec3 playerLoc) {
    glm::mat4 transform = getQuadModel(face,0,0,0);


    QuadTree *t = new QuadTree(this, QUAD_WIDTH,transform, eye, playerLoc,MAX_DEPTH,face, SPLITTING_DISTANCE);
    t->draw();
    delete t;
}


void PlanetManager::drawQuad(int face, int depth, int x, int y) {

    GLuint shader = m_graphics->getActiveProgram();
    glm::mat4 model = getQuadModel(face, depth, x, y);
    glUniformMatrix4fv(glGetUniformLocation(shader,"cube_m"),1,GL_FALSE,glm::value_ptr(model));
    m_tile->draw();

}

float PlanetManager::getNoise(glm::vec3 loc) {
    /* Remake framebuffers */
    m_graphics->setActiveProgram("pre");
    m_fb->bind();
    GLuint shader = m_graphics->getActiveProgram();

    glUniform1i(glGetUniformLocation(shader, "collisionDetection"), 1);
    glUniform3fv(glGetUniformLocation(shader,"collisionLoc"),1,glm::value_ptr(loc));
    loadNoiseTexture(shader);

    m_graphics->sendEmptyMatrices();
    m_graphics->drawShape("fullscreenQuad");



    GLfloat pixels[4];
    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_FLOAT, pixels);

    m_fb->unbind();

    return float(pixels[0]);
}

/**
 * @brief PlanetManager::getQuadModel
 * @param face
 * @param depth
 * @param x
 * @param y
 * @return a model matrix that transforms a point on a QUAD_WIDTH by QUAD_WIDTH grid of 1x1 squares on the XZ plane
 * with the left corner at the origin to its corresponding point on the sphere
 */
glm::mat4 PlanetManager::getQuadModel(int face, int depth, int x, int y) {
    glm::mat4 model = glm::mat4();

    switch(face) {
    case TOP:
        model = glm::translate(model, glm::vec3(0, .5f, 0));
        break;
    case BOTTOM:
        model = glm::translate(model, glm::vec3(0, -.5f, 0));
        model = model * glm::rotate(glm::radians(180.f), glm::vec3(0.f,0.f,1.f));
        break;
    case LEFT:
        model = glm::translate(model, glm::vec3(-.5f, 0, 0));
        model = model * glm::rotate(glm::radians(90.f), glm::vec3(1.f,0.f,0.f));
        model = model * glm::rotate(glm::radians(90.f), glm::vec3(0.f,0.f,1.f));
        break;
    case RIGHT:
        model = glm::translate(model, glm::vec3(.5f, 0, 0));
        model = model * glm::rotate(glm::radians(90.f), glm::vec3(1.f,0.f,0.f));
        model = model * glm::rotate(glm::radians(-90.f), glm::vec3(0.f,0.f,1.f));
        break;
    case FRONT:
        model = glm::translate(model, glm::vec3(0.f, 0.f, .5f));
        model = model * glm::rotate(glm::radians(90.f), glm::vec3(1.f,0.f,0.f));
        break;
    case BACK:
        model = glm::translate(model, glm::vec3(0, 0, -.5f));
        model = model * glm::rotate(glm::radians(-180.f), glm::vec3(0.f,0.f,1.f));
        model = model * glm::rotate(glm::radians(-90.f), glm::vec3(1.f,0.f,0.f));
        break;
    }

    model = glm::translate(model,glm::vec3((float)x/glm::pow(2,depth),0, (float)y/glm::pow(2,depth)));
    model = glm::translate(model, glm::vec3(-.5, 0.f, -.5));
    model = glm::scale(model,glm::vec3(1.f)*(1.f/(QUAD_WIDTH*glm::pow(2,depth))));

    return model;
}

Graphics *PlanetManager::getGraphics() {
    return m_graphics;
}



void PlanetManager::initializeQuad(int width) {
    m_tile = new TileShape(width);
}

void PlanetManager::initializeNoiseTexture() {
    /* Open image file */
    QImage image(":/images/noise.png");
    image = QGLWidget::convertToGLFormat(image);

    /* Generate texture */
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
//    glGenerateMipmap(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, 0);

}

void PlanetManager::loadNoiseTexture(GLuint shader){
    /* Bind texture */
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1i(glGetUniformLocation(shader, "tex"), GL_TEXTURE0);

}

