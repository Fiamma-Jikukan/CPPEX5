#ifndef GRAPH_H
#define GRAPH_H
#include <ostream>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

template<class T>
class Graph {
private:
    vector<T> vertices;
    vector<vector<double> > adjList;

public:
    Graph();

    ~Graph();

    Graph(const Graph &other);

    Graph &operator=(const Graph &other);

    int getVertexIndex(T vertex) const;

    void AddVertex(T vertex);

    void RemoveVertex(T vertex);

    void AddEdge(T source, T target, double weight);

    void RemoveEdge(T source, T target);

    void SetWeight(T source, T target, double weight);

    double GetWeight(T source, T target);

    vector<T> GetNeighbors(T vertex) const;

    vector<T> GetConnected(T vertex) const;

    vector<T> GetSources(T target);

    void PrintGraph();

    friend ostream &operator<<(ostream &os, const Graph<T> &graph) {
        const unsigned int size = graph.vertices.size();
        for (unsigned int i = 0; i < size; i++) {
            T vertex = graph.vertices[i];
            vector<T> neighbors = graph.GetNeighbors(vertex);
            os << vertex << ": ";
            for (unsigned int j = 0; j < neighbors.size(); j++) {
                T neighbor = neighbors[j];
                os << neighbor << " ";
            }
            os << endl;
        }
        return os;
    }
};


#endif //GRAPH_H
