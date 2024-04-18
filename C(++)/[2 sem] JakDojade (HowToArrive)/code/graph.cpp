#include "Graph.h"
#include "PrQueue.h"

using namespace std;

Graph::Graph(int vertices) {
    this->verticesNum = vertices;
    this->VertexNames = new MyString *[vertices];
    adjList = new Node *[vertices];
    for (int i = 0; i < vertices; i++) { adjList[i] = nullptr; }
}

Graph::Graph(const Graph &other) {
    this->verticesNum = other.verticesNum;
    this->VertexNames = new MyString *[verticesNum];
    adjList = new Node *[verticesNum];
    for (int i = 0; i < verticesNum; i++) {
        adjList[i] = nullptr;
        Node *curr = other.adjList[i];
        while (curr != nullptr) {
            Node *newNode = new Node;
            newNode->dest = curr->dest;
            newNode->weight = curr->weight;
            newNode->next = adjList[i];
            adjList[i] = newNode;
            curr = curr->next;
        }
    }
}

Graph &Graph::operator=(const Graph &other) {
    if (this != &other) {
        for (int i = 0; i < verticesNum; i++) {
            Node *curr = adjList[i];
            while (curr != nullptr) {
                Node *temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] adjList;
        delete[] VertexNames;

        this->verticesNum = other.verticesNum;
        this->VertexNames = new MyString *[verticesNum];
        adjList = new Node *[verticesNum];
        for (int i = 0; i < verticesNum; i++) {
            adjList[i] = nullptr;
            Node *curr = other.adjList[i];
            while (curr != nullptr) {
                Node *newNode = new Node;
                newNode->dest = curr->dest;
                newNode->weight = curr->weight;
                newNode->next = adjList[i];
                adjList[i] = newNode;
                curr = curr->next;
            }
        }
    }
    return *this;
}

Graph::~Graph() {
    for (int i = 0; i < verticesNum; i++) {
        Node *curr = adjList[i];
        while (curr != nullptr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] adjList;
    delete[] VertexNames;
}

void Graph::addEdge(City *u, City *v, int weight, bool isDirected) {
    Node *newNode = new Node;
    newNode->dest = v;
    newNode->weight = weight;
    newNode->next = adjList[u->index];
    adjList[u->index] = newNode;

    if (!isDirected) {
        // Create opposite edge
        newNode = new Node;
        newNode->dest = u;
        newNode->weight = weight;
        newNode->next = adjList[v->index];
        adjList[v->index] = newNode;
    }
}

void Graph::addVertexName(City *city) {
    this->VertexNames[city->index] = city->name;
}

int Graph::getShortestPath(City *source, City *dest) const {
    PrQueue queue;
    int *dist = new int[verticesNum];
    int *prev = new int[verticesNum];
    bool *visited = new bool[verticesNum];
    for (int i = 0; i < verticesNum; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }
    queue.insert(source->index, 0);
    dist[source->index] = 0;

    while (!queue.isEmpty()) {
        int u = queue.pop();
        if (visited[u]) continue;
        else visited[u] = true;

        if (u == dest->index) break;

        Node *curr = adjList[u];
        while (curr != nullptr) {
            int v = curr->dest->index;
            int weight = curr->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                queue.insert(v, dist[v]);
            }
            curr = curr->next;
        }
    }
    int result = dist[dest->index];
    delete[] dist;
    delete[] prev;
    delete[] visited;
    return result;
}

int
Graph::getShortestPathWithCities(City *source, City *dest, MyString *citiesVisited, int *citiesVisitedAmount) const {
    PrQueue queue;
    int *dist = new int[verticesNum];
    int *prev = new int[verticesNum];
    bool *visited = new bool[verticesNum];
    for (int i = 0; i < verticesNum; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }
    queue.insert(source->index, 0);
    dist[source->index] = 0;

    while (!queue.isEmpty()) {
        int u = queue.pop();
        if (visited[u]) continue;
        else visited[u] = true;

        if (u == dest->index) break;

        Node *curr = adjList[u];
        while (curr != nullptr) {
            int v = curr->dest->index;
            int weight = curr->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                queue.insert(v, dist[v]);
            }
            curr = curr->next;
        }
    }

    int result = dist[dest->index];

    int curr = dest->index;
    int i = 0;
    while (curr != -1) {
        citiesVisited[i] = *(VertexNames[curr]);
        curr = prev[curr];
        i++;
    }
    *citiesVisitedAmount = i;

    delete[] dist;
    delete[] prev;
    delete[] visited;
    return result;
}