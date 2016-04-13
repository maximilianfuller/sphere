#include "NavMesh.h"

#include "util/obj.h"

#include "engine/graphics/Graphics.h"
#include "engine/intersect/Ray.h"
#include "engine/intersect/Triangle.h"

#include <QMutableListIterator>

NavMesh::NavMesh(QList<Triangle *> triangleData, Graphics *graphics) :
    m_vertexCount(0),
    triangles(triangleData)
{
    filterTriangles();
    createVBO(graphics);
    createGraph();
}

bool NavMesh::vertexEquals(glm::vec3 v1, glm::vec3 v2)
{
    glm::vec3 diff = v1 - v2;
    return glm::length2(diff) <= VEQUAL_EPS;
}

float NavMesh::triangleArea(glm::vec3 apex, glm::vec3 p1, glm::vec3 p2)
{
    glm::vec3 v1 = apex - p1;
    glm::vec3 v2 = p2 - p1;

    return glm::cross(v1, v2).y;
}

bool NavMesh::hasVertex(Triangle *t, glm::vec3 v)
{
    return vertexEquals(v, t->vertices[0]) || vertexEquals(v, t->vertices[1])
            || vertexEquals(v, t->vertices[2]);
}

glm::vec3 NavMesh::getRightEndpoint(Portal portal, glm::vec3 apex)
{
    glm::vec3 v1 = portal.first - apex;
    glm::vec3 v2 = portal.second - portal.first;

    if(glm::cross(v1, v2).y >= 0)
    {
        return portal.first;
    }
    else
    {
        return portal.second;
    }
}

glm::vec3 NavMesh::getLeftEndpoint(Portal portal, glm::vec3 apex)
{
    glm::vec3 v1 = portal.first - apex;
    glm::vec3 v2 = portal.second - portal.first;

    if(glm::cross(v1, v2).y > 0)
    {
        return portal.second;
    }
    else
    {
        return portal.first;
    }
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

void NavMesh::resetVisited()
{
    foreach(const Node n, m_graph)
    {
        n.value->visited = false;
    }
}

bool NavMesh::getPath(glm::vec3 startPos, glm::vec3 endPos, Triangle *start, Triangle *end, QList<glm::vec3> &path)
{
    PortalPath portals;

    if(!getPortals(start, end, portals))
    {
        resetVisited();
        return false;
    }
    else
    {
        resetVisited();
    }

    portals.prepend(Portal(startPos, startPos));
    portals.append(Portal(endPos, endPos));

    /* String pulling */
    glm::vec3 apex = portals[0].first;
    glm::vec3 right = getRightEndpoint(portals[1], apex);
    glm::vec3 left = getLeftEndpoint(portals[1], apex);

    int rightIndex = 2;
    int leftIndex = 2;

    path.append(apex);

    for(int i = 2; i < portals.size(); i++)
    {
        glm::vec3 tempRight = getRightEndpoint(portals[i], apex);
        glm::vec3 tempLeft = getLeftEndpoint(portals[i], apex);

        glm::vec3 newRight = 0.99f * tempRight + 0.01f * tempLeft;
        glm::vec3 newLeft = 0.01f * tempRight + 0.99f * tempLeft;

        if(triangleArea(apex, right, newRight) <= 0)
        {
            // Tighten funnel
            if(vertexEquals(apex, right) || triangleArea(apex, left, newRight) >= 0)
            {
                right = newRight;
                rightIndex = i;
            }
            // Right crossed over left
            else
            {
                // Reset funnel at left endpoint
                path.append(left);

                i = leftIndex;
                rightIndex = leftIndex;

                apex = left;
                left = apex;
                right = apex;
                continue;
            }
        }

        if(triangleArea(apex, left, newLeft) >= 0)
        {
            // Tighten funnel
            if(vertexEquals(apex, left) || triangleArea(apex, newLeft, right) >= 0)
            {
                left = newLeft;
                leftIndex = i;
            }
            // Left crossed over right
            else
            {
                // Reset funnel at left endpoint
                path.append(right);

                i = rightIndex;
                leftIndex = rightIndex;

                apex = right;
                left = apex;
                right = apex;
                continue;
            }
        }
    }

    path.append(endPos);
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
    graphics->sendUseTextureUniform(0);
    graphics->sendUseLightingUniform(0);
    graphics->sendModelUniform(glm::mat4x4());
    graphics->sendColorUniform(glm::vec4(0, 1, 0, 0.5));
    graphics->drawShape("navMesh");
}
