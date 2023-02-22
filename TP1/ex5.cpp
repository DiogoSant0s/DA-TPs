// By: Gonçalo Leão

#include "exercises.h"

bool IntroGraph::isDAG() const {
    for (auto v : vertexSet) {
        v -> setVisited(false);
        v -> setProcesssing(false);
    }
    for (auto v : vertexSet) {
        if (!v -> isVisited()) {
            if (!dfsIsDAG(v)) {
                return false;
            }
        }
    }
    return true;
}

bool IntroGraph::dfsIsDAG(Vertex *v) const {
    v -> setVisited(true);
    v -> setProcesssing(true);
    for (auto e : v -> getAdj()) {
        auto w = e -> getDest();
        if (w -> isProcessing()) {
            return false;
        }
        if (!w -> isVisited()) {
            if (!dfsIsDAG(w)) {
                return false;
            }
        }
    }
    v -> setProcesssing(false);
    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, test_isDAG) {
    IntroGraph myGraph;

    for (int i = 0; i < 6; i++) {
        myGraph.addVertex(i);
    }

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(myGraph.isDAG(), true);

    myGraph.addEdge(4, 1, 0);

    EXPECT_EQ(myGraph.isDAG(), false);
}