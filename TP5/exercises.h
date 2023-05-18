// By: Gonçalo Leão

#ifndef DA_TP5_CLASSES_EXERCISES_H
#define DA_TP5_CLASSES_EXERCISES_H

#include <string>
#include <cmath>
#include <vector>
#include <sstream>
using namespace std;

// Ex 1
// Recursive version
unsigned long factorialRecurs(unsigned long n);
// Version with dynamic programming
unsigned long factorialDP(unsigned long n);
// Ex 2
bool changeMakingUnlimitedDP(const unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]);
// Ex 3
bool changeMakingDP(const unsigned int C[], const unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);
// Ex 4
string calcSum(const int sequence[], unsigned long n);
void testPerformanceCalcSum();
// Ex 5
unsigned long s_recursive(unsigned int n, unsigned int k);
unsigned long b_recursive(unsigned int n);
unsigned long s_dynamic(unsigned int n, unsigned int k);
unsigned long b_dynamic(unsigned int n);
// Ex 6
int maxSubsequenceDP(const int A[], unsigned int n, unsigned int &i, unsigned int &j);
int maxSubsequenceBF(const int A[], unsigned int n, unsigned int &i, unsigned int &j);
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j);
void testPerformanceMaxSubsequence();
// Ex 7
string hanoiDP(unsigned int n, char src, char dest);
// Ex 8
unsigned int knapsackDP(const unsigned int values[], const unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
// Ex 9
int editDistance(string pattern, string text);
float numApproximateStringMatching(const string& filename, const string& toSearch);

#include "../data_structures/Graph.h"

class DPGraph: public Graph {
public:
    // Ex 10
    void dijkstra(const int &origin);
    vector<int> getPath(const int &origin, const int &dest) const;
    // Ex 11
    void bellmanFord(const int &origin);
    // Ex 12
    void floydWarshall();
    vector<int> getFloydWarshallPath(const int &origin, const int &dest) const;
protected:
    /**
    * Analyzes an edge in single source shortest path algorithm.
    * Returns true if the target vertex was relaxed (dist, path).
    * Used by all single-source shortest path algorithms.
    */
    static bool relax(Edge *edge);
};

#endif //DA_TP5_CLASSES_EXERCISES_H
