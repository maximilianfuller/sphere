#include "quadtree.h"
#include "planetmanager.h"
#include <QList>
#include <util/ResourceLoader.h>

QuadTree::QuadTree(PlanetManager *pm, int quadWidth, glm::mat4 transform, glm::vec3 eye,
                   glm::vec3 look, int maxDepth, int face, float splittingDistance)
{
    m_quadWidth = quadWidth;
    m_transform = transform;
    m_eye = eye;
    m_look = look;
    m_root = new Node(NULL);
    m_maxDepth = maxDepth;
    m_face = face;
    m_pm = pm;
    m_splittingDistance = splittingDistance;

    generateTree(m_root, 0, 0, 0);

}

QuadTree::~QuadTree() {
    delete m_root;
}

void QuadTree::draw() {
    drawHelper(m_root, 0, 0, 0);
}

void QuadTree::drawHelper(Node * current, int x, int y, int depth) {
    if(current->isLeaf()) {
        if(!shouldCull(x, y, depth)) {
            m_pm->drawQuad(m_face, depth, x, y);
        }
    } else {
        drawHelper(current->children[0], x*2, y*2, depth+1);
        drawHelper(current->children[1], x*2+1, y*2, depth+1);
        drawHelper(current->children[2], x*2+1, y*2+1, depth+1);
        drawHelper(current->children[3], x*2, y*2+1, depth+1);
    }
}

void QuadTree::generateTree(Node *current, int x, int y, int depth) {

    if(depth < m_maxDepth && shouldSplit(x, y, depth)) {
        current->generateChildren();
        generateTree(current->children[0], x*2, y*2, depth+1);
        generateTree(current->children[1], x*2+1, y*2, depth+1);
        generateTree(current->children[2], x*2+1, y*2+1, depth+1);
        generateTree(current->children[3], x*2, y*2+1, depth+1);
    }
}

bool QuadTree::shouldSplit(int x, int y, int depth) {
    float distance = getDistance(x,y,depth);
    distance = glm::min(getDistance(x, y+1, depth), distance);
    distance = glm::min(getDistance(x+1, y, depth), distance);
    distance = glm::min(getDistance(x+1, y+1, depth), distance);
    distance = glm::min(getDistance(x+.5f, y+.5f, depth), distance);
    float level = -glm::log(distance)/glm::log(2.f);
    level+=m_splittingDistance;

    return level > depth;

}

/**
 * @brief QuadTree::shouldCull
 * @param x
 * @param y
 * @param depth
 * @return whether or not the given tile should be drawn
 */
bool QuadTree::shouldCull(int x, int y, int depth) {

    return false;

    glm::vec3 x1 = getWorldLoc(x, y, depth)*(1.f + PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x2 = getWorldLoc(x+1, y, depth)*(1.f + PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x3 = getWorldLoc(x, y+1, depth)*(1.f + PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x4 = getWorldLoc(x+1, y+1, depth)*(1.f + PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x5 = x1*(1.f + PlanetManager::TILE_MAX_HEIGHT - PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x6 = x2*(1.f + PlanetManager::TILE_MAX_HEIGHT - PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x7 = x3*(1.f + PlanetManager::TILE_MAX_HEIGHT - PlanetManager::TILE_MIN_HEIGHT);
    glm::vec3 x8 = x4*(1.f + PlanetManager::TILE_MAX_HEIGHT - PlanetManager::TILE_MIN_HEIGHT);

    bool facingAway =
            glm::dot(x1-m_eye, x1) > PlanetManager::DOT_PRODUCT_EPSILON &&
            glm::dot(x2-m_eye, x2) > PlanetManager::DOT_PRODUCT_EPSILON &&
            glm::dot(x3-m_eye, x3) > PlanetManager::DOT_PRODUCT_EPSILON &&
            glm::dot(x4-m_eye, x4) > PlanetManager::DOT_PRODUCT_EPSILON;

    if(facingAway) {
        return true;
    }

    Graphics *g = m_pm->getGraphics();

    QList<glm::vec3> points;
    points.append(x1);
    points.append(x2);
    points.append(x3);
    points.append(x4);
    points.append(x5);
    points.append(x6);
    points.append(x7);
    points.append(x8);

    bool allCornersOutside = true;
    for(int j = 0; j < points.size(); j++) {
        if(g->inFrustum(points.value(j))) {
            allCornersOutside = false;
            break;
        }
    }
    if (allCornersOutside) {
        return true;
    }

    return false;
}

/**
 * @brief QuadTree::getDistance
 * @param x
 * @param y
 * @param depth
 * @return distance in world space from point on sphere (given by grid location) to eye
 */
float QuadTree::getDistance(float x, float y, int depth) {
    return glm::distance(getWorldLoc(x, y, depth), glm::normalize(m_eye));
}


glm::vec3 QuadTree::getWorldLoc(float x, float y, int depth) {
    int width = glm::pow(2, depth);
    glm::vec4 loc = m_transform*glm::vec4((x/width)*m_quadWidth, 0.f, (y/width)*m_quadWidth, 1.f);
    return glm::normalize(glm::vec3(loc.x, loc.y, loc.z));
}





