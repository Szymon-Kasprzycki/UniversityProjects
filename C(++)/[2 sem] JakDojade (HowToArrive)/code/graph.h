#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include "iostream"
#include "City.h"
#include "HashMap.h"

struct Node {
    City *dest;
    int weight;
    Node *next;
};

class Graph {
    int verticesNum;
    Node **adjList;
    MyString **VertexNames;

public:
    explicit Graph(int vertices);

    Graph(const Graph &other);

    Graph &operator=(const Graph &other);

    ~Graph();

    void addEdge(City *u, City *v, int weight, bool isDirected);

    void addVertexName(City *city);

    int getShortestPath(City *source, City *dest) const;

    int getShortestPathWithCities(City *source, City *dest, MyString *citiesVisited, int *citiesVisitedAmount) const;
};


#endif //TEST_GRAPH_H
