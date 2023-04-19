#include "TestAux.h"

/**
 * Auxiliary functions to tests...
 *
 */
DPGraph CreateTestGraph() {
    DPGraph myGraph;

    for (int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    return myGraph;
}

DPGraph CreateTestGraph2() {
    DPGraph myGraph;

    for (int i = 1; i <= 4; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 1, 0);
    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 3, 2.5);
    myGraph.addEdge(1, 4, 6);

    myGraph.addEdge(2, 1, 2);
    myGraph.addEdge(2, 2, 0);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(2, 4, INF);

    myGraph.addEdge(3, 1, 2.5);
    myGraph.addEdge(3, 2, 1);
    myGraph.addEdge(3, 3, 0);
    myGraph.addEdge(3, 4, 5);

    myGraph.addEdge(4, 1, 6);
    myGraph.addEdge(4, 2, INF);
    myGraph.addEdge(4, 3, 5);
    myGraph.addEdge(4, 4, 0);

    return myGraph;
}


void generateRandomGridGraph(int n, DPGraph& g) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g.addVertex(i*n + j);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if ((di != 0) != (dj != 0) && i + di >= 0 && i + di < n && j + dj >= 0 && j + dj < n)
                        g.addEdge(i * n + j, (i + di) * n + (j + dj), dis(gen));
}

void checkAllPaths(DPGraph& g, const string& expected) {
    stringstream ss;
    vector<Vertex*> vs = g.getVertexSet();
    for (auto& v : vs) {
        ss << v->getId() << "<-";
        if (v->getPath() != nullptr) {
            ss << v->getPath()->getOrig()->getId();
        }
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

void checkSinglePath(const vector<int>& path, const string& expected) {
    stringstream ss;
    for (int i : path) {
        ss << i << " ";
    }
    EXPECT_EQ(expected, ss.str());
}