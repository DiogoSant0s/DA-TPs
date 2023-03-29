// By: Gonçalo Leão

#ifndef DA_TP3_CLASSES_EXERCISES_H
#define DA_TP3_CLASSES_EXERCISES_H

// Ex 1
bool changeMakingGR(const unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);
// Ex 2
#include <vector>

class Activity {
public:
    unsigned int start;
    unsigned int finish;
    Activity(unsigned int s, unsigned int f) : start(s), finish(f) {};
    bool operator==(const Activity &a2) const;
    bool operator<(const Activity &a2) const;
};
std::vector<Activity> activitySelectionGR(std::vector<Activity> A);

// Ex 3
double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks);
// Ex 4
double fractionalKnapsackGR(const unsigned int values[], const unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]);

#include "../data_structures/Graph.h"

class GreedyGraph: public Graph {
public:
    // Ex 5
    std::vector<Vertex*> prim();
    // Ex 6
    std::vector<Vertex*> kruskal();
    // Ex 7
    void edmondsKarp(int source, int target);
protected:
    // TODO: Add auxiliary methods if needed
    void dfsKruskalPath(Vertex *v);

    static void testAndVisit(std::queue<Vertex *> &q, Edge *e, Vertex *w, double residual);

    bool findAugmentingPath(Vertex *s, Vertex *t);

    static double findMinResidualAlongPath(Vertex *s, Vertex *t);

    static void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
};

#endif //DA_TP3_CLASSES_EXERCISES_H
