// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/24.

#include <iomanip>
#include "Graph.h"

MSTGraph::MSTGraph() {
    uint32_t animalCount;
    cin >> animalCount;
    edges.reserve(animalCount*2);
    nodes.reserve(animalCount);
    int x, y;
    for (uint32_t i = 0; i < animalCount; ++i) {
        cin >> x >> y;
        nodes.emplace_back(x, y);
    }
}

//void MSTGraph::addEdge(uint32_t u, uint32_t v) {
//    if (v > u) {
//        edges.push_back(u);
//        edges.push_back(v);
//    } else {
//        edges.push_back(v);
//        edges.push_back(u);
//    }
//}

//void MSTGraph::printEdges() {
//    cout << std::fixed << std::setprecision(2) <<  this->weight << "\n";
//    for (size_t i = 0; i < this->edges.size(); ++i) {
//        cout << this->edges[i];
//        ++i;
//        cout << " ";
//        cout << this->edges[i];
//        cout << "\n";
//    }
//}

Graph::Graph() {
    uint32_t animalCount;
    cin >> animalCount;
//    edges.reserve(animalCount*2);
    nodes.reserve(animalCount);
    int x, y;
    for (uint32_t i = 0; i < animalCount; ++i) {
        cin >> x >> y;
        nodes.emplace_back(x, y);
    }
}

//void Graph::addEdge(uint32_t u, uint32_t v) {
//    if (v > u) {
//        edges.push_back(u);
//        edges.push_back(v);
//    } else {
//        edges.push_back(v);
//        edges.push_back(u);
//    }
//}

//void Graph::printEdges() {
//    cout << std::fixed << std::setprecision(2) <<  this->weight << "\n";
//    for (size_t i = 0; i < this->edges.size(); ++i) {
//        cout << this->edges[i];
//        ++i;
//        cout << " ";
//        cout << this->edges[i];
//        cout << "\n";
//    }
//}

