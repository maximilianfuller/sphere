#ifndef NAVMESH_H
#define NAVMESH_H

#include "util/CommonIncludes.h"
#include <QMultiHash>
#include <QVector>
#include <QPair>
#include <QList>
#include <QQueue>

class Graphics;
class Ray;
struct TriangleData;
struct CollisionData;

typedef QPair<glm::vec3, glm::vec3> Portal;
typedef QList<Portal> PortalPath;

class NavMesh
{
public:
    NavMesh(QList<TriangleData *> triangleData, Graphics *graphics);

    void toggleVisible();

    bool getPath(glm::vec3 start, glm::vec3 end, QList<glm::vec3> &path);
    bool getPortals(glm::vec3 start, glm::vec3 end, PortalPath &path);

    void draw(Graphics *graphics);

private:
    void filterTriangles();
    void createGraph();
    void createVBO(Graphics *graphics);
    void addTriangleFloats(TriangleData *tri);

    TriangleData *getTriangle(QPair<int, int> key);
    TriangleData *getTriangleRay(Ray &ray, CollisionData &data);
    TriangleData *getTriangleBelow(glm::vec3 pos, CollisionData &data);

    bool getPortalsHelper(QPair<TriangleData *, PortalPath> curPair, TriangleData *goal,
                       PortalPath &portals,
                       QQueue<QPair<TriangleData *, PortalPath> > &toVisit);

    QList<TriangleData *> m_triangles;
    QMultiHash<QPair<int, int>, TriangleData *> m_graph;

    QVector<float> m_vboData;
    int m_vertexCount;

    bool m_visible;
};

#endif // NAVMESH_H
