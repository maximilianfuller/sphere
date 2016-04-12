#include "NavMesh.h"

#include "util/obj.h"

#include "engine/graphics/Graphics.h"
#include "engine/intersect/Ray.h"
#include "engine/intersect/Triangle.h"

#include <QMutableListIterator>

NavMesh::NavMesh(QList<Triangle *> triangleData, Graphics *graphics) :
    m_vertexCount(0),
    m_visible(false),
    triangles(triangleData)
{
    filterTriangles();
    createVBO(graphics);
    createGraph();
}

void NavMesh::toggleVisible()
{
    m_visible = !m_visible;
}

bool NavMesh::vertexEquals(glm::vec3 v1, glm::vec3 v2)
{
    glm::vec3 diff = v1 - v2;
    return glm::length2(diff) <= VEQUAL_EPS;
}

bool NavMesh::hasVertex(Triangle *t, glm::vec3 v)
{
    return vertexEquals(v, t->vertices[0]) || vertexEquals(v, t->vertices[1])
            || vertexEquals(v, t->vertices[2]);
}

void NavMesh::filterTriangles()
{
    QMutableListIterator<Triangle *> iter(triangles);

    while(iter.hasNext())
    {
        Triangle *cur = iter.next();

        if(cur->normal.y <= 0)
        {
            iter.remove();
        }
    }
}

void NavMesh::createGraph()
{
    for(int i = 0; i < triangles.size(); i++)
    {
        Triangle *t1 = triangles[i];

        for(int j = i + 1; j < triangles.size(); j++)
        {
            Triangle *t2 = triangles[j];
            Node n1, n2;

            n1.value = t1;
            n2.value = t2;

            if(m_graph.contains(t1))
            {
                n1 = m_graph[t1];
            }

            if(m_graph.contains(t2))
            {
                n2 = m_graph[t2];
            }

            if(hasVertex(t2, t1->vertices[0]) && hasVertex(t2, t1->vertices[1]))
            {
                n1.edges.append(Portal(t1->vertices[0], t1->vertices[1]));
                n1.neighbors.append(t2);
                n2.edges.append(Portal(t1->vertices[0], t1->vertices[1]));
                n2.neighbors.append(t1);
            }
            else if(hasVertex(t2, t1->vertices[1]) && hasVertex(t2, t1->vertices[2]))
            {
                n1.edges.append(Portal(t1->vertices[1], t1->vertices[2]));
                n1.neighbors.append(t2);
                n2.edges.append(Portal(t1->vertices[1], t1->vertices[2]));
                n2.neighbors.append(t1);
            }
            else if(hasVertex(t2, t1->vertices[2]) && hasVertex(t2, t1->vertices[0]))
            {
                n1.edges.append(Portal(t1->vertices[2], t1->vertices[0]));
                n1.neighbors.append(t2);
                n2.edges.append(Portal(t1->vertices[2], t1->vertices[0]));
                n2.neighbors.append(t1);
            }

            m_graph.insert(t1, n1);
            m_graph.insert(t2, n2);
        }
    }
}

void NavMesh::createVBO(Graphics *graphics)
{
    /* Create VBO data */
    glm::vec3 delta = glm::vec3(0, 0.1, 0);

    foreach(Triangle *triangle, triangles)
    {
        Triangle nTriangle(triangle->vertices[0] + delta,
                triangle->vertices[1] + delta,
                triangle->vertices[2] + delta);

        addTriangleFloats(&nTriangle);
    }

    /* Add shape */
    graphics->createShape(m_vboData.data(),
                          m_vboData.size() * sizeof(float),
                          m_vertexCount, "navMesh");

}

void NavMesh::addTriangleFloats(Triangle *tri)
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

bool NavMesh::getPath(Triangle *start, Triangle *end, QList<glm::vec3> &path)
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

bool NavMesh::getPortals(Triangle *start, Triangle *end, PortalPath &portals)
{
    /* Create start node and path */
    Node startNode = m_graph[start];

    PortalPath startPortalPath;
    QPair<Node, PortalPath> startPair = QPair<Node, PortalPath>(startNode, startPortalPath);

    /* Call helper */
    QQueue<QPair<Node, PortalPath> > toVisit;
    bool ret = getPortalsHelper(startPair, end, portals, toVisit);

    return ret;
}

bool NavMesh::getPortalsHelper(QPair<Node, PortalPath> curPair, Triangle *goal,
                               PortalPath &portals,
                               QQueue<QPair<Node, PortalPath> > &toVisit)
{
    Node cur = curPair.first;

    if(cur.value == goal)
    {
        portals = curPair.second;

        return true;
    }
    else if(cur.value->visited && toVisit.isEmpty())
    {
        return false;
    }
    else if(!cur.value->visited)
    {
        cur.value->visited = true;

        /* Add possibilities to Queue */
        for(int i = 0; i < cur.neighbors.size(); i++)
        {
            PortalPath nextPortalPath = curPair.second;
            nextPortalPath.append(cur.edges[i]);
            QPair<Node, PortalPath> nextPair(m_graph[cur.neighbors[i]], nextPortalPath);
            toVisit.enqueue(nextPair);
        }
    }

    /* Visit next */
    QPair<Node, PortalPath> next = toVisit.dequeue();
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
