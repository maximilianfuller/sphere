#include "planetmanager.h"
#include "tileshape.h"
#include "planetshape.h"
#include "util/ResourceLoader.h"
#include "quadtree.h"


PlanetManager::PlanetManager()
{
    initializeQuad(QUAD_WIDTH);
    initializeNoiseTexture();
    m_shader = ResourceLoader::loadShaders(":/shaders/planet.vert",":/shaders/shader.frag");
    m_ratio = glm::vec2(16.f, 9.f);
    m_fov = 45.f;
}

void PlanetManager::drawPlanet(glm::vec3 eye, glm::vec3 look) {

//    std::cout << glm::to_string(look) << std::endl;

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//    glUseProgram(m_shader);

    //set uniforms
    glm::mat4 view = getViewMatrix(eye, look);
    glm::mat4 proj = getProjectionMatrix();
    glm::mat4 model = glm:: mat4(); //can customize this later

    glUniformMatrix4fv(glGetUniformLocation(m_shader,"v"),1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_shader,"p"),1,GL_FALSE,glm::value_ptr(proj));
    glUniformMatrix4fv(glGetUniformLocation(m_shader,"m"),1,GL_FALSE,glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(m_shader,"color"),1,glm::value_ptr(glm::vec3(1.f, 1.f, 1.f)));
    glUniform1i(glGetUniformLocation(m_shader, "collisionDetection"),0);

    //set noise texture



    //draw faces of cube
    drawFace(TOP, eye, look);
    drawFace(BOTTOM, eye, look);
    drawFace(LEFT, eye, look);
    drawFace(RIGHT, eye, look);
    drawFace(FRONT, eye, look);
    drawFace(BACK, eye, look);

//    getNoise(glm::normalize(eye));

}

void PlanetManager::drawFace(int face, glm::vec3 eye, glm::vec3 look) {
    glm::mat4 transform = getQuadModel(face,0,0,0);


    QuadTree *t = new QuadTree(this, QUAD_WIDTH,transform, eye,look,MAX_DEPTH,face, SPLITTING_DISTANCE);
    t->draw();
    delete t;
}


void PlanetManager::drawQuad(int face, int depth, int x, int y) {

    glm::mat4 model = getQuadModel(face, depth, x, y);
    glUniformMatrix4fv(glGetUniformLocation(m_shader,"cube_m"),1,GL_FALSE,glm::value_ptr(model));
    m_tile->draw();

}

glm::vec3 PlanetManager::getNoise(glm::vec3 loc) {

    GLuint color_tex;
    GLuint fb;


    //-------------------------
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    //RGBA8 2D texture, 24 bit depth texture, 256x256
    glGenTextures(1, &color_tex);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //NULL means reserve texture memory, but texels are undefined
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 256, 256, 0, GL_RGB16F, GL_FLOAT, NULL);


    //Attach 2D texture to this FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex, 0);
    //-------------------------
    //Does the GPU support current FBO configuration?
//       assert(GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER));
    //assert(GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER));

    //and now you can render to GL_TEXTURE_2D
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //-------------------------
    glViewport(0, 0, 256, 256);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //-------------------------
    //**************************
    glm::mat4 model = glm::mat4();
    model = model * glm::rotate(glm::radians(90.f), glm::vec3(1.f,0.f,0.f));
    model = glm::translate(model,glm::vec3(-1.f, 0.f, -1.f));
    model = glm::scale(model,glm::vec3(2.f, 2.f, 2.f));

    glUniformMatrix4fv(glGetUniformLocation(m_shader,"m"),1,GL_FALSE,glm::value_ptr(model));
    glUniform1i(glGetUniformLocation(m_shader, "collisionDetection"),1);
    TileShape(1).draw();
    //-------------------------
    GLfloat pixels[4];
    glReadPixels(0, 0, 1, 1, GL_RGB16F, GL_FLOAT, pixels);

    float h = pixels[3];

    //std::cout << "height value!  " << glm::to_string(h) << std::endl;
    //pixels 0, 1, 2 should be white
    //pixel 4 should be black
    //----------------
    //Bind 0, which means render to back buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


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

glm::mat4 PlanetManager::getProjectionMatrix() {
    float fov = glm::radians(m_fov);
    float aspect = m_ratio.x/m_ratio.y;
    float near = NEAR_CLIPPING_PLANE;
    float far = FAR_CLIPPING_PLANE;

    return glm::perspective(fov, aspect, near, far);
}

glm::mat4 PlanetManager::getViewMatrix(glm::vec3 eye, glm::vec3 look) {
    glm::vec3 center = eye + look;
    glm::vec3 up(0,1,0);

    return glm::lookAt(eye, center, up);
}

void PlanetManager::initializeQuad(int width) {
    m_tile = new TileShape(width);
}

void PlanetManager::initializeNoiseTexture() {
//    QImage img(path);
//    if(img.isNull()) {
//        return;
//    }
//    img = QGLWidget::convertToGLFormat(img);

//    GLuint imageID;
//    glGenTextures(1, &imageID);

//    m_textures->insert(path, imageID);

//    glBindTexture(GL_TEXTURE_2D, imageID);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
//    glBindTexture(GL_TEXTURE_2D, 0);
}

void PlanetManager::setRatio(glm::vec2 ratio) {
    m_ratio = ratio;
}

