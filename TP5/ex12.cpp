// By: Gonçalo Leão

#include "exercises.h"
#include "TestAux.h"

void DPGraph::floydWarshall() {
    unsigned n = vertexSet.size();
    deleteMatrix(distMatrix, (int) n);
    deleteMatrix(pathMatrix, (int) n);
    distMatrix = new double *[n];
    pathMatrix = new int *[n];
    for (unsigned i = 0; i < n; i++) {
        distMatrix[i] = new double[n];
        pathMatrix[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            distMatrix[i][j] = i == j ? 0 : INF;
            pathMatrix[i][j] = -1;
        }
        for (auto e : vertexSet[i]->getAdj()) {
            int j = findVertexIdx(e->getDest()->getId());
            distMatrix[i][j] = e->getWeight();
            pathMatrix[i][j] = (int) i;
        }
    }
    for (unsigned k = 0; k < n; k++) {
        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < n; j++) {
                if (distMatrix[i][k] == INF || distMatrix[k][j] == INF)
                    continue;
                double val = distMatrix[i][k] + distMatrix[k][j];
                if (val < distMatrix[i][j]) {
                    distMatrix[i][j] = val;
                    pathMatrix[i][j] = pathMatrix[k][j];
                }
            }
        }
    }
}

vector<int> DPGraph::getFloydWarshallPath(const int &origin, const int &dest) const{
    vector<int> res;
    int i = findVertexIdx(origin);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || distMatrix[i][j] == INF)
        return res;
    for (;j != -1; j = pathMatrix[i][j])
        res.push_back(vertexSet[j]->getId());
    reverse(res.begin(), res.end());
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex12, test_floydWarshall) {
    DPGraph myGraph = CreateTestGraph();
    myGraph.floydWarshall();
    checkSinglePath(myGraph.getFloydWarshallPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getFloydWarshallPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getFloydWarshallPath(7, 1), "7 6 4 3 1 ");
}