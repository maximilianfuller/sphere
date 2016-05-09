#ifndef PLANETMANAGER_H
#define PLANETMANAGER_H

#include <util/CommonIncludes.h>

class TileShape;
class Graphics;

class PlanetManager
{
public:
    PlanetManager(Graphics *graphics);
    void drawPlanet(glm::vec3 eye, glm::vec3 look);
    void setRatio(glm::vec2 ratio);
    glm::mat4 getQuadModel(int face, int depth, int x, int y);
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix(glm::vec3 eye, glm::vec3 look);
    void drawQuad(int face, int depth, int x, int y);
    glm::vec3 getNoise(glm::vec3 loc);
    const static float TILE_MAX_HEIGHT = .2f; //these are used to determin tile volume frustum culling
    const static float TILE_MIN_HEIGHT = 0.f;
    const static float DOT_PRODUCT_EPSILON = .1f; //used to determin dot product threshold of sphere normal and dir vector
                                                  //when considering tile for backface culling


private:

    const static int TOP = 0;
    const static int BOTTOM = 1;
    const static int LEFT = 2;
    const static int RIGHT = 3;
    const static int FRONT = 4;
    const static int BACK = 5;
    const static int NUM_FACES = 6;
    const static int QUAD_WIDTH = 128;
    const static int MAX_DEPTH = 12;
    const static float SPLITTING_DISTANCE = 0.0f;



    float m_fov;
    glm::vec2 m_ratio;
    const static float NEAR_CLIPPING_PLANE = .00001f;
    const static float FAR_CLIPPING_PLANE = 1000.f;

    void drawFace(int face, glm::vec3 eye, glm::vec3 look);

    void initializeQuad(int width);
    void initializeNoiseTexture();
    TileShape *m_tile;
    Graphics *m_graphics;
};



#endif // PLANETMANAGER_H
