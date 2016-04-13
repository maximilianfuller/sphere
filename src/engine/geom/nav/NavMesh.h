#ifndef NAVMESH_H
#define NAVMESH_H

#include "util/CommonIncludes.h"
#include <QMultiHash>
#include <QVector>
#include <QPair>
#include <QList>
#include <QQueue>

typedef QPair<glm::vec3, glm::vec3> Portal;
typedef QList<Portal> PortalPath;

class Graphics;
class Ray;
struct Triangle;
struct CollisionData;

struct Node
{
    Triangle *value;
    QList<Triangle *> neighbors;
    QList<Portal> edges;
};

const float VEQUAL_EPS = 0.01;

class NavMesh
{
public:
    NavMesh(QList<Triangle *> triangleData, Graphics *graphics);

    bool getPath(glm::vec3 startPos, glm::vec3 endPos, Triangle *start, Triangle *end, QList<glm::vec3> &path);
    bool getPortals(Triangle *start, Triangle *end, PortalPath &path);

    void draw(Graphics *graphics);

    QList<Triangle *> triangles;

private:
    bool vertexEquals(glm::vec3 v1, glm::vec3 v2);
    float triangleArea(glm::vec3 apex, glm::vec3 p1, glm::vec3 p2);
    bool hasVertex(Triangle *t, glm::vec3 v);

    glm::vec3 getRightEndpoint(Portal portal, glm::vec3 apex);
    glm::vec3 getLeftEndpoint(Portal portal, glm::vec3 apex);

    void filterTriangles();
    void createGraph();
    void createVBO(Graphics *graphics);
    void addTriangleFloats(Triangle *tri);
    void resetVisited();

    bool getPortalsHelper(QPair<Node, PortalPath> curPair, Triangle *goal,
                       PortalPath &portals,
                       QQueue<QPair<Node, PortalPath> > &toVisit);

    QHash<Triangle *, Node> m_graph;

    QVector<float> m_vboData;
    int m_vertexCount;
};

#endif // NAVMESH_H
