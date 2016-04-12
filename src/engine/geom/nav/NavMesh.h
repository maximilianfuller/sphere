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

    void toggleVisible();

    bool getPath(Triangle *start, Triangle *end, QList<glm::vec3> &path);
    bool getPortals(Triangle *start, Triangle *end, PortalPath &path);

    void draw(Graphics *graphics);

    QList<Triangle *> triangles;

private:
    bool vertexEquals(glm::vec3 v1, glm::vec3 v2);
    bool hasVertex(Triangle *t, glm::vec3 v);

    void filterTriangles();
    void createGraph();
    void createVBO(Graphics *graphics);
    void addTriangleFloats(Triangle *tri);

    bool getPortalsHelper(QPair<Node, PortalPath> curPair, Triangle *goal,
                       PortalPath &portals,
                       QQueue<QPair<Node, PortalPath> > &toVisit);

    QHash<Triangle *, Node> m_graph;

    QVector<float> m_vboData;
    int m_vertexCount;

    bool m_visible;
};

#endif // NAVMESH_H
