#ifndef GRAPH_H
#define GRAPH_H
#include <ostream>
#include <vector>
using namespace std;

template<class T>
class Graph {
private:
    vector<T> vertices;
    vector<vector<double>> adjList;

public:
    Graph();
    ~Graph();
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);

    unsigned int getVertexIndex(T vertex);
    void AddVertex(T vertex);
    void RemoveVertex(T vertex);
    void AddEdge(T source, T target, double weight);
    void RemoveEdge(T source, T target);
    void SetWeight(T source, T target, double weight);
    double GetWeight(T source, T target);
    vector<T> GetNeighbors(T vertex);
    vector<T> GetConnected(T vertex);
    vector<T> GetSources(T target);
    void PrintGraph();
    friend ostream& operator<<(ostream& os, const Graph& graph);




};


#endif //GRAPH_H
