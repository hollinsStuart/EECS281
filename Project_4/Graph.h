// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/24.

#ifndef PROJECT_4_GRAPH_H
#define PROJECT_4_GRAPH_H

#include <iostream>
using std::cout, std::cin;
#include <vector>
using std::vector;
#include <cstdint>
#include "Node.h"

class MSTGraph {
public:
    MSTGraph();
    ~MSTGraph() = default;

//    void addEdge(uint32_t u, uint32_t v);

    /* the edges should be already in order */
//    void printEdges();

    vector<MSTNode> nodes{};
    vector<uint32_t> edges{};
    double weight{};
};


class Graph {
public:
    Graph();
    ~Graph() = default;

//    void addEdge(uint32_t u, uint32_t v);

    /* the edges should be already in order */
//    void printEdges();

    vector<Node> nodes{};
//    vector<uint32_t> edges{};
    double weight{};
};


#endif //PROJECT_4_GRAPH_H
