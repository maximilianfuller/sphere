#include "NavMesh.h"

#include "util/obj.h"

#include "engine/graphics/Graphics.h"
#include "engine/intersect/Ray.h"
#include "engine/intersect/Triangle.h"

#include <QMutableListIterator>

NavMesh::NavMesh(QList<TriangleData *> triangleData, Graphics *graphics) :
    m_vertexCount(0),
    m_visible(false),
    m_triangles(triangleData)
{
    filterTriangles();
    createGraph();
    createVBO(graphics);
}

void NavMesh::toggleVisible()
{
    m_visible = !m_visible;
}

void NavMesh::filterTriangles()
{
    QMutableListIterator<TriangleData *> iter(m_triangles);

    while(iter.hasNext())
    {
        TriangleData *cur = iter.next();

        if(cur->normal.y <= 0)
        {
            iter.remove();
        }
    }
}

void NavMesh::createGraph()
{
    foreach(TriangleData *triangle, m_triangles)
    {
        int minAB = triangle->a.vertexIndex < triangle->b.vertexIndex
                ? triangle->a.vertexIndex : triangle->b.vertexIndex;
        int maxAB = triangle->a.vertexIndex >= triangle->b.vertexIndex
                ? triangle->a.vertexIndex : triangle->b.vertexIndex;

        int minBC = triangle->b.vertexIndex < triangle->c.vertexIndex
                ? triangle->b.vertexIndex : triangle->c.vertexIndex;
        int maxBC = triangle->b.vertexIndex >= triangle->c.vertexIndex
                ? triangle->b.vertexIndex : triangle->c.vertexIndex;

        int minAC = triangle->a.vertexIndex < triangle->c.vertexIndex
                ? triangle->a.vertexIndex : triangle->c.vertexIndex;
        int maxAC = triangle->a.vertexIndex >= triangle->c.vertexIndex
                ? triangle->a.vertexIndex : triangle->c.vertexIndex;

        m_graph.insert(QPair<int, int>(minAB, maxAB), triangle);
        m_graph.insert(QPair<int, int>(minBC, maxBC), triangle);
        m_graph.insert(QPair<int, int>(minAC, maxAC), triangle);
    }
}

void NavMesh::createVBO(Graphics *graphics)
{
    /* Create VBO data */
    glm::vec3 delta = glm::vec3(0, 0.1, 0);

    foreach(TriangleData * triangle, m_triangles)
    {
        triangle->vertices[0] += delta;
        triangle->vertices[1] += delta;
        triangle->vertices[2] += delta;

        addTriangleFloats(triangle);
    }

    /* Add shape */
    graphics->createShape(m_vboData.data(),
                          m_vboData.size() * sizeof(float),
                          m_vertexCount, "navMesh");

}

void NavMesh::addTriangleFloats(TriangleData *tri)
{
    for (int i = 0; i < 3; i++) {
        m_vboData.append(tri->vertices[i].x);
        m_vboData.append(tri->vertices[i].y);
        m_vboData.append(tri->vertices[i].z);
        m_vboData.append(tri->normal.x);
        m_vboData.append(tri->normal.y);
        m_vboData.append(tri->normal.z);
        m_vboData.append(0);
        m_vboData.append(0);

        m_vertexCount += 1;
    }
}

TriangleData *NavMesh::getTriangle(QPair<int, int> key)
{
    QHash<QPair<int, int>, TriangleData *>::iterator iter = m_graph.find(key);

    while(iter != m_graph.end() && iter.key() == key)
    {
        if(!(*iter)->visited)
        {
            return *iter;
        }
    }

    return NULL;
}

TriangleData *NavMesh::getTriangleRay(Ray &ray, CollisionData &data)
{
    foreach(TriangleData *tData, m_triangles)
    {
        Triangle triangle = Triangle(tData->vertices[0],
                tData->vertices[1], tData->vertices[2]);

        if(ray.intersectTriangle(triangle, data))
        {
            return tData;
        }
    }

    return NULL;
}

TriangleData *NavMesh::getTriangleBelow(glm::vec3 pos, CollisionData &data)
{
    Ray ray = Ray(pos, glm::vec3(0, -1, 0));

    return getTriangleRay(ray, data);
}

bool NavMesh::getPath(glm::vec3 start, glm::vec3 end, QList<glm::vec3> &path)
{
    PortalPath portals;

    getPortals(start, end, portals);

    /* Midpoint method */
    foreach(Portal portal, portals)
    {
        path.append((portal.first + portal.second) / 2.f);
    }

    /* TODO: SSF */
}

bool NavMesh::getPortals(glm::vec3 start, glm::vec3 end, PortalPath &portals)
{
    /* Create start node and path */
    CollisionData dataStart, dataEnd;
    TriangleData *startT = getTriangleBelow(start, dataStart);
    TriangleData *endT = getTriangleBelow(end, dataEnd);

    start.y = start.y - dataStart.t;
    end.y = end.y - dataEnd.t;

    PortalPath startPortalPath;
    startPortalPath.append(Portal(start, start));
    QPair<TriangleData *, PortalPath> startPair = QPair<TriangleData *, PortalPath>(startT, startPortalPath);

    /* Call helper */
    QQueue<QPair<TriangleData *, PortalPath> > toVisit;
    bool ret = getPortalsHelper(startPair, endT, portals, toVisit);

    /* Add destination portal */
    portals.append(Portal(end, end));

    return ret;
}

bool NavMesh::getPortalsHelper(QPair<TriangleData *, PortalPath> curPair, TriangleData *goal,
                               PortalPath &portals,
                               QQueue<QPair<TriangleData *, PortalPath> > &toVisit)
{
    TriangleData *cur = curPair.first;

    if(cur == goal)
    {
        portals = curPair.second;
        return true;
    }
    else if(cur->visited && toVisit.isEmpty())
    {
        return false;
    }
    else if(!cur->visited)
    {
        cur->visited = true;

        /* Add possibilities to Queue */
        int minAB = cur->a.vertexIndex < cur->b.vertexIndex
                ? cur->a.vertexIndex : cur->b.vertexIndex;
        int maxAB = cur->a.vertexIndex >= cur->b.vertexIndex
                ? cur->a.vertexIndex : cur->b.vertexIndex;

        int minBC = cur->b.vertexIndex < cur->c.vertexIndex
                ? cur->b.vertexIndex : cur->c.vertexIndex;
        int maxBC = cur->b.vertexIndex >= cur->c.vertexIndex
                ? cur->b.vertexIndex : cur->c.vertexIndex;

        int minAC = cur->a.vertexIndex < cur->c.vertexIndex
                ? cur->a.vertexIndex : cur->c.vertexIndex;
        int maxAC = cur->a.vertexIndex >= cur->c.vertexIndex
                ? cur->a.vertexIndex : cur->c.vertexIndex;

        TriangleData *ta = getTriangle(QPair<int, int>(minAB, maxAB));
        TriangleData *tb = getTriangle(QPair<int, int>(minBC, maxBC));
        TriangleData *tc = getTriangle(QPair<int, int>(minAC, maxAC));

        /* Make sure that nodes exist */
        if(ta)
        {
            PortalPath nextPortalPath = curPair.second;
            nextPortalPath.append(Portal(cur->vertices[0], cur->vertices[1]));
            QPair<TriangleData *, PortalPath> nextPair(ta, nextPortalPath);
            toVisit.enqueue(nextPair);
        }

        if(tb)
        {
            PortalPath nextPortalPath = curPair.second;
            nextPortalPath.append(Portal(cur->vertices[1], cur->vertices[2]));
            QPair<TriangleData *, PortalPath> nextPair(tb, nextPortalPath);
            toVisit.enqueue(nextPair);
        }

        if(tc)
        {
            PortalPath nextPortalPath = curPair.second;
            nextPortalPath.append(Portal(cur->vertices[0], cur->vertices[2]));
            QPair<TriangleData *, PortalPath> nextPair(tc, nextPortalPath);
            toVisit.enqueue(nextPair);
        }
    }

    /* Visit next */
    QPair<TriangleData *, PortalPath> next = toVisit.dequeue();
    return getPortalsHelper(next, goal, portals, toVisit);
}

void NavMesh::draw(Graphics *graphics)
{
    if(m_visible)
    {
        graphics->sendUseTextureUniform(0);
        graphics->sendUseLightingUniform(0);
        graphics->sendModelUniform(glm::mat4x4());
        graphics->sendColorUniform(glm::vec4(0, 1, 0, 0.5));
        graphics->drawShape("navMesh");
    }
}
