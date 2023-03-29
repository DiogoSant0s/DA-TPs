#include "exercises.h"

void GreedyGraph::testAndVisit(std::queue<Vertex*> &q, Edge* e, Vertex* w, double residual) {
    if (!w -> isVisited() && residual > 0) {
        w -> setVisited(true);
        w -> setPath(e);
        q.push(w);
    }
}

bool GreedyGraph::findAugmentingPath(Vertex* s, Vertex* t) {
    for (auto v : vertexSet) {
        v -> setVisited(false);
    }
    s -> setVisited(true);
    std::queue<Vertex*> q;
    q.push(s);
    while(!q.empty() && !t -> isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v -> getAdj()) {
            testAndVisit(q, e, e -> getDest(), e -> getWeight() - e -> getFlow());
        }
        for (auto e: v -> getIncoming()) {
            testAndVisit(q, e, e -> getOrig(), e -> getFlow());
        }
    }
    return t -> isVisited();
}

double GreedyGraph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v -> getPath();
        if (e -> getDest() == v) {
            f = std::min(f, e -> getWeight() - e -> getFlow());
            v = e -> getOrig();
        }
        else {
            f = std::min(f, e -> getFlow());
            v = e -> getDest();
        }
    }
    return f;
}

void GreedyGraph::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v -> getPath();
        double flow = e -> getFlow();
        if (e -> getDest() == v) {
            e -> setFlow(flow + f);
            v = e -> getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e -> getDest();
        }
    }
}

void GreedyGraph::edmondsKarp(int source, int target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e -> setFlow(0);
        }
    }
    // Loop to find augmentation paths
    while(findAugmentingPath(s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex7, test_edmondsKarp) {
    GreedyGraph myGraph;
    for (int i = 1; i <= 6; i++) {
        myGraph.addVertex(i);
    }
    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);
    myGraph.edmondsKarp(1, 6);
    std::stringstream ss;
    for (auto v : myGraph.getVertexSet()) {
        ss << v -> getId() << "-> (";
        for (const auto e : v -> getAdj())
            ss << (e -> getDest()) -> getId() << "[Flow: " << e -> getFlow() << "] ";
        ss << ") || ";
    }
    std::cout << ss.str() << std::endl << std::endl;
    EXPECT_EQ("1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ", ss.str());
}
