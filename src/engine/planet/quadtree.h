#ifndef QUADTREE_H
#define QUADTREE_H


#include <util/CommonIncludes.h>

class PlanetManager;

struct Node {
    Node *parent;
    Node *children[4]; //CC ORDER STARTING WITH TOP LEFT (TL, TR, BR, BL)
    Node *neighbors[4]; //CC ORDER STARTING WITH TOP (T, R, B, L)
    bool shouldCull;

    Node(Node *parent) {
        this->parent = parent;
        for(int i = 0; i < 4; i++) {
            children[i] = NULL;
            neighbors[i] = NULL;
        }
    }

    ~Node() {
        for(int i = 0; i < 4; i++) {
            delete children[i];
        }
    }

    bool isLeaf() {
        return !children[0];
    }

    void generateChildren() {
        for(int i = 0; i < 4; i++) {
            children[i] = new Node(this);
        }
    }
};

class QuadTree
{
public:
    QuadTree(PlanetManager *pm, int quadWidth, glm::mat4 transform, glm::vec3 eye,
             glm::vec3 playerLoc, int maxDepth, int face, float splittingDistance);
    ~QuadTree();
    void draw();
private:
    Node *m_root;
    int m_quadWidth;
    int m_maxDepth;
    glm::mat4 m_transform;
    glm::vec3 m_eye;
    glm::vec3 m_playerLoc;
    int m_face;
    PlanetManager *m_pm;
    float m_splittingDistance;

    bool shouldSplit(int x, int y, int depth);
    void generateTree(Node *current, int x, int y, int depth);
    void drawHelper(Node * current, int x, int y, int depth);
    glm::vec3 getWorldLoc(float x, float y, int depth);
    float getDistance(float x, float y, int depth);
    bool shouldCull(int x, int y, int depth);
};



#endif // QUADTREE_H
