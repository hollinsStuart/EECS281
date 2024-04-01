// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include <iostream>
using std::cout, std::cin, std::cerr, std::endl, std::getline;
#include <cstdint>
#include <iomanip>
#include "Graph.h"
#include "FastTSP.h"

/* insertion */
void fast_tsp_insertion() {
    Graph graph;
    vector<uint32_t> path(2, 0);    // 0, ..., 0
    path.reserve(graph.nodes.size()+1);

    uint32_t newParentIndex{};    // node num | index in the path
    /* find node with the shortest distance from the path*/
    for (uint32_t i = 1; i < (uint32_t)graph.nodes.size(); ++i) {
        /* for node[i] */
        double deltaDistance = std::numeric_limits<double>::infinity();
        for (size_t j = 0; j < path.size() - 1; ++j) {
            double leftDistance = distance(graph.nodes[path[j]], graph.nodes[i]),
                   rightDistance = distance(graph.nodes[path[j+1]], graph.nodes[i]);
            /* distance with path[j], path[j+1] */
            double curDistance = leftDistance + rightDistance
                    - distance(graph.nodes[path[j]], graph.nodes[path[j+1]]);
            if (curDistance < deltaDistance) {
                deltaDistance = curDistance;
                newParentIndex = (uint32_t)j;
            }
        }
        path.insert(path.begin()+newParentIndex+1, i);
    }
    graph.weight = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        graph.weight += distance(graph.nodes[path[i]], graph.nodes[path[i+1]]);
    }
    cout << std::fixed << std::setprecision(2) <<  graph.weight << "\n";
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cout << path[i] << " ";
    }
}

/* neighbor with 2-OPT */
void fast_tsp_neighbor() {
    Graph graph;
    vector<uint32_t> path(2, 0);
    path.reserve(graph.nodes.size());

    cout << std::fixed << std::setprecision(2) <<  graph.weight << "\n";
    for (size_t i = 0; i < graph.nodes.size() - 1; ++i) {
        cout << path[i] << " ";
    }
}
