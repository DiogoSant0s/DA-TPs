// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"

std::vector<int> IntroGraph::dfs(const int & source) const {
    std::vector<int> res;
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    for (auto v : vertexSet) {
        v -> setVisited(false);
    }
    dfsVisit(s, res);
    return res;
}

void IntroGraph::dfsVisit(Vertex *v, std::vector<int> & res) const {
    v -> setVisited(true);
    res.push_back(v -> getId());
    for (auto & e : v -> getAdj()) {
        auto w = e -> getDest();
        if (!w -> isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, test_dfs) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<int> vs = graph.dfs(1);

    unsigned int ids[] = {1, 2, 5, 6, 3, 7, 4};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}