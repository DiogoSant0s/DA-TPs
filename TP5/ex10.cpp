// By: Gonçalo Leão

#include "exercises.h"
#include "TestAux.h"

bool DPGraph::relax(Edge *edge) {
    if (edge->getOrig()->getDist() + edge->getWeight() < edge->getDest()->getDist()) {
        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWeight());
        edge->getDest()->setPath(edge);
        return true;
    }
    else
        return false;
}

void DPGraph::dijkstra(const int &origin) {
    for (auto v : vertexSet) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    auto s = findVertex(origin);
    s->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    while(!q.empty() ) {
        auto v = q.extractMin();
        for (auto e : v->getAdj()) {
            auto oldDist = e->getDest()->getDist();
            if (relax(e)) {
                if (oldDist == INF) {
                    q.insert(e->getDest());
                }
                else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

vector<int> DPGraph::getPath(const int &origin, const int &dest) const{
    vector<int> res;
    auto v = findVertex(dest);
    if (v == nullptr || v->getDist() == INF) {
        return res;
    }
    res.push_back(v->getId());
    while (v->getPath() != nullptr) {
        v = v->getPath()->getOrig();
        res.push_back(v->getId());
    }
    reverse(res.begin(), res.end());
    if (res.empty() || res[0] != origin) {
        cout << "Origin not found!!" << endl;
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

void testPerformanceDijkstra() {
    //Change these const parameters as needed
    for (int n = 10; n <= 100; n += 10) {
        DPGraph g;
        cout << "Dijkstra generating grid " << n << " x " << n << " ..." << endl;
        generateRandomGridGraph(n, g);
        cout << "Dijkstra processing grid " << n << " x " << n << " ..." << endl;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g.dijkstra(i*n + j);
        auto finish = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        cout << "Dijkstra processing grid " << n << " x " << n << " average time (micro-seconds)=" << (elapsed / (n*n)) << endl;
    }
}

TEST(TP5_Ex10, test_dijkstra) {
    DPGraph myGraph = CreateTestGraph();

    myGraph.dijkstra(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.dijkstra(1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(myGraph.getPath(1, 7), "1 2 4 5 7 ");

    myGraph.dijkstra(5);
    checkSinglePath(myGraph.getPath(5, 6), "5 7 6 ");

    myGraph.dijkstra(7);
    checkSinglePath(myGraph.getPath(7, 1), "7 6 4 3 1 ");

    // Uncomment the next line to perform the execution time tests
    //testPerformanceDijkstra();
}