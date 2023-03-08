// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "../data_structures/MutablePriorityQueue.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    explicit Vertex(int id);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    void setId(int Id);
    void setVisited(bool Visited);
    void setProcesssing(bool Processing);
    void setIndegree(unsigned int Indegree);
    void setDist(double Dist);
    void setPath(Edge *Path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);
    friend class MutablePriorityQueue<Vertex>;
protected:
    int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges
    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree{}; // used by topsort
    double dist = 0;
    Edge *path = nullptr;
    std::vector<Edge *> incoming; // incoming edges
    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, double w);
    Vertex* getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex* getOrig() const;
    Edge* getReverse() const;
    double getFlow() const;
    void setSelected(bool Selected);
    void setReverse(Edge *Reverse);
    void setFlow(double Flow);
protected:
    Vertex* dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    // auxiliary fields
    bool selected = false;
    // used for bidirectional edges
    Vertex* orig;
    Edge* reverse = nullptr;
    double flow{}; // for flow-related problems
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */