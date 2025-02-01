#include "Graph.h"

#include <iostream>
#include <ostream>

template class Graph<int>;

template<class T>
Graph<T>::Graph() : vertices({}), adjList({{}}) {
}

template<class T>
Graph<T>::~Graph() = default;

template<class T>
Graph<T>::Graph(const Graph &other) : vertices(other.vertices), adjList(other.adjList) {
}

template<class T>
Graph<T> &Graph<T>::operator=(const Graph &other) = default;

template<class T>
unsigned int Graph<T>::getVertexIndex(T vertex) {
    if (vertices.size() == 0) {
        return -1;
    }
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Graph<T>::AddVertex(T vertex) {
    unsigned int index = Graph<T>::getVertexIndex(vertex);
    unsigned int size = vertices.size();
    if (index == -1) {
        vertices.push_back(vertex);
        for (unsigned int i = 0; i <= size; i++) {
            adjList[i].push_back(0);
        }
        const vector<double> new_vertex(size + 1, 0);
        adjList.push_back(new_vertex);
    }
}

template<class T>
void Graph<T>::RemoveVertex(T vertex) {
    unsigned int index = Graph<T>::getVertexIndex(vertex);
    if (index == -1) {
        return;
    }
    vertices.erase(vertices.begin() + index);
    adjList.erase(adjList.begin() + index);
    for (unsigned int i = 0; i < vertices.size(); i++) {
        adjList[i].erase(adjList[i].begin() + index);
    }
}

template<class T>
void Graph<T>::AddEdge(T source, T target, const double weight) {
    unsigned int source_index = Graph<T>::getVertexIndex(source);
    unsigned int target_index = Graph<T>::getVertexIndex(target);
    if (source_index == -1) {
        AddVertex(source);
    }
    if (target_index == -1) {
        AddVertex(target);
    }
    source_index = Graph<T>::getVertexIndex(source);
    target_index = Graph<T>::getVertexIndex(target);
    adjList[source_index][target_index] = weight;
}

template<class T>
void Graph<T>::RemoveEdge(T source, T target) {
    const unsigned int source_index = Graph<T>::getVertexIndex(source);
    const unsigned int target_index = Graph<T>::getVertexIndex(target);
    adjList[source_index][target_index] = 0.0;
}

template<class T>
void Graph<T>::SetWeight(T source, T target, const double weight) {
    const unsigned int source_index = Graph<T>::getVertexIndex(source);
    const unsigned int target_index = Graph<T>::getVertexIndex(target);
    adjList[source_index][target_index] = weight;
}

template<class T>
double Graph<T>::GetWeight(T source, T target) {
    const unsigned int source_index = Graph<T>::getVertexIndex(source);
    const unsigned int target_index = Graph<T>::getVertexIndex(target);
    return adjList[source_index][target_index];
}

template<class T>
vector<T> Graph<T>::GetNeighbors(T vertex) {
    const unsigned int index = Graph<T>::getVertexIndex(vertex);
    vector<T> neighbors;
    for (unsigned int i = 0; i < adjList[index].size(); i++) {
        if (adjList[index][i] != 0) {
            neighbors.push_back(vertices[i]);
        }
    }
    return neighbors;
}

template<class T>
vector<T> Graph<T>::GetConnected(T vertex) {

}

template<class T>
vector<T> Graph<T>::GetSources(T target) {
    const unsigned int target_index = Graph<T>::getVertexIndex(target);
    vector<T> sources;
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (adjList[i][target_index] != 0) {
            sources.push_back(vertices[i]);
        }
    }
    return sources;

}

template<class T>
void Graph<T>::PrintGraph() {
    const unsigned int size = vertices.size();
    for (unsigned int i = 0; i < size; i++) {
        T vertex = vertices[i];
        vector<T> neighbors = GetNeighbors(vertex);
        cout << vertex << ": ";
        for (unsigned int j = 0; j < neighbors.size(); j++) {
            T neighbor = neighbors[j];
            cout << neighbor << " ";
        }
        cout << endl;
    }

}

