#include "Graph.h"


template class Graph<string>;

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
Graph<T>::Graph(Graph &&other) noexcept
    : vertices(std::move(other.vertices)),
      adjList(std::move(other.adjList)) {
}

template<class T>
Graph<T> &Graph<T>::operator=(Graph &&other) noexcept {
    if (this == &other)
        return *this;
    vertices = std::move(other.vertices);
    adjList = std::move(other.adjList);
    return *this;
}

template<class T>
int Graph<T>::getVertexIndex(T vertex) const {
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
    const int index = getVertexIndex(vertex);
    const unsigned int size = vertices.size();
    if (index == -1) {
        vertices.push_back(vertex);
        for (unsigned int i = 0; i <= size; i++) {
            adjList[i].push_back(0.0);
        }
        const vector<double> new_vertex(size + 1, 0);
        adjList.push_back(new_vertex);
    }
}

template<class T>
void Graph<T>::RemoveVertex(T vertex) {
    const int index = getVertexIndex(vertex);
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
    int source_index = getVertexIndex(source);
    int target_index = getVertexIndex(target);
    // if there are no vertices, add them
    if (source_index == -1) {
        AddVertex(source);
    }
    if (target_index == -1) {
        AddVertex(target);
    }
    source_index = getVertexIndex(source);
    target_index = getVertexIndex(target);
    if ((adjList[source_index][target_index] == 0) || (
            adjList[source_index][target_index] != 0 && adjList[source_index][target_index] > weight)) {
        // first condition: there is no Edge
        // second condition: the new weight is smaller than the previous one
        adjList[source_index][target_index] = weight;
    }
}

template<class T>
void Graph<T>::RemoveEdge(T source, T target) {
    const int source_index = getVertexIndex(source);
    const int target_index = getVertexIndex(target);
    if (source_index == -1 || target_index == -1) {
        return;
    }
    adjList[source_index][target_index] = 0.0;
}

template<class T>
void Graph<T>::SetWeight(T source, T target, const double weight) {
    const int source_index = getVertexIndex(source);
    const int target_index = getVertexIndex(target);
    if (source_index == -1 || target_index == -1) {
        return;
    }
    adjList[source_index][target_index] = weight;
}

template<class T>
double Graph<T>::GetWeight(T source, T target) {
    const int source_index = getVertexIndex(source);
    const int target_index = getVertexIndex(target);
    if (source_index == -1 || target_index == -1) {
        return 0.0;
    }
    return adjList[source_index][target_index];
}

template<class T>
vector<T> Graph<T>::GetNeighbors(T vertex) const {
    const unsigned int index = getVertexIndex(vertex);
    vector<T> neighbors;
    for (unsigned int i = 0; i < adjList[index].size(); i++) {
        if (adjList[index][i] != 0) {
            neighbors.push_back(vertices[i]);
        }
    }
    return neighbors;
}

template<class T>
vector<T> Graph<T>::GetConnected(T vertex) const {
    unordered_set<T> already_explored; // a set to keep track on who was already added
    vector<T> connected; // final vector
    deque<T> q; // the queue will keep all elements that needs to be explored
    q.push_back(vertex);
    while (q.empty() == false) {
        T current = q.front();
        q.pop_front();
        if (already_explored.insert(current).second == false) {
            continue; // skip the element that was already explored
        }
        // if we reached this point, the current element is not in the connected vector, it's neighbors needs to be explored
        connected.push_back(current);
        vector<T> neighbors = GetNeighbors(current);
        for (unsigned int i = 0; i < neighbors.size(); i++) {
            q.push_back(neighbors[i]);
        }
    }
    connected.erase(connected.begin()); // remove self
    return connected;
}

template<class T>
vector<T> Graph<T>::GetSources(T target) {
    const unsigned int target_index = getVertexIndex(target);
    vector<T> sources;
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (adjList[i][target_index] != 0) {
            sources.push_back(vertices[i]);
        }
    }
    return sources;
}
