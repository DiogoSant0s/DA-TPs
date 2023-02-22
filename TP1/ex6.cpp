// By: Gonçalo Leão

#include "exercises.h"
#include "TestAux.h"

std::vector<std::vector<int>> IntroGraph::computeSCCs() const {
    std::vector<std::vector<int>> sccs;
    for (auto v : vertexSet) {
        v -> setVisited(false);
    }
    std::stack<Vertex*> vertexStack;
    for (auto v : vertexSet) {
        if(!v -> isVisited()) {
            firstDfsKosarajuSharir(v, vertexStack);
        }
    }
    for (auto v : vertexSet) {
        v -> setVisited(false);
    }
    while(!vertexStack.empty()) {
        Vertex * v = vertexStack.top();
        vertexStack.pop();
        if(!v -> isVisited()) {
            std::vector<int> scc;
            secondDfsKosarajuSharir(v, scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}

void IntroGraph::firstDfsKosarajuSharir(Vertex *v, std::stack<Vertex *> &vertexStack) const {
    v -> setVisited(true);
    for (auto e : v -> getAdj()) {
        auto w = e -> getDest();
        if(!w -> isVisited()) {
            firstDfsKosarajuSharir(w, vertexStack);
        }
    }
    vertexStack.push(v);
}

void IntroGraph::secondDfsKosarajuSharir(Vertex *v, std::vector<int> & res) const {
    v -> setVisited(true);
    res.push_back(v->getId());
    for (auto& e : v -> getIncoming()) {
        auto w = e -> getOrig();
        if (!w -> isVisited()) {
            secondDfsKosarajuSharir(w, res);
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, test_SCC) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<std::vector<int>> sccs = graph.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3,5,6), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(7)));

    IntroGraph graph2;
    for(int i = 1; i <= 5; i++) {
        graph2.addVertex(i);
    }
    graph2.addEdge(1,3,0);
    graph2.addEdge(1,4,0);
    graph2.addEdge(2,1,0);
    graph2.addEdge(3,2,0);
    graph2.addEdge(4,5,0);
    sccs = graph2.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(5)));
}