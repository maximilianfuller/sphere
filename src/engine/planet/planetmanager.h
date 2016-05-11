#ifndef PLANETMANAGER_H
#define PLANETMANAGER_H

#include <util/CommonIncludes.h>

class TileShape;
class Graphics;
class Framebuffer;

class PlanetManager
{
public:
    PlanetManager(Graphics *graphics);
    void drawPlanet(glm::vec3 eye, glm::vec3 playerLoc);
    void setRatio(glm::vec2 ratio);
    glm::mat4 getQuadModel(int face, int depth, int x, int y);
    Graphics *getGraphics();
    void drawQuad(int face, int depth, int x, int y);
    float getNoise(glm::vec3 loc);
    const static float TILE_MAX_HEIGHT = 0.f; //these are used to determin tile volume frustum culling
    const static float TILE_MIN_HEIGHT = 0.f;
    const static float DOT_PRODUCT_EPSILON = .1f; //used to determine dot product threshold of sphere normal and dir vector
                                                  //when considering tile for backface culling

private:

    const static int TOP = 0;
    const static int BOTTOM = 1;
    const static int LEFT = 2;
    const static int RIGHT = 3;
    const static int FRONT = 4;
    const static int BACK = 5;
    const static int NUM_FACES = 6;

    //MAIN PLANET PARAMETERS
    const static int QUAD_WIDTH = 16;
    const static int MAX_DEPTH = 8;
    const static float SPLITTING_DISTANCE = 1.3f;


    void drawFace(int face, glm::vec3 eye, glm::vec3 playerLoc);
    void initializeNoiseTexture();
    void loadNoiseTexture(GLuint shader);
    void initializeQuad(int width);
    TileShape *m_tile;
    Graphics *m_graphics;
    Framebuffer *m_fb;
    GLuint m_texture;
};



#endif // PLANETMANAGER_H
