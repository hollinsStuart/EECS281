// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include <cstdint>
#include <algorithm>
#include <string>
using std::string;
#include <iomanip>
#include "MST.h"
#include "Graph.h"

/* using Prim's algorithm */
void mst(double (*dist)(const MSTNode&, const MSTNode&)) {
    MSTGraph graph;
    vector<bool> inner(graph.nodes.size(), false);
    inner[0] = true;
    vector<uint32_t> parent(graph.nodes.size(), 0);
    vector<double> distances(graph.nodes.size(), 0);
    for (size_t i = 1; i < graph.nodes.size(); ++i) {
        distances[i] = dist(graph.nodes[0], graph.nodes[i]);
    }
    distances[0] = std::numeric_limits<double>::infinity();
    uint32_t numNode = 1;
    while (numNode != graph.nodes.size()) {
        /* add edge */
        auto minElement = std::min_element(distances.begin(), distances.end());
        uint32_t outerNode = (uint32_t)(minElement - distances.begin());
        inner[outerNode] = true;
        graph.weight += *minElement;
        *minElement = std::numeric_limits<double>::infinity();
        ++numNode;

        /* update distances */
        for (size_t i = 0; i < graph.nodes.size(); ++i) {
            if (!inner[i]) {
                /* for node[i] outside the graph */
                double newDistance = dist(graph.nodes[i], graph.nodes[outerNode]);
                if (newDistance < distances[i]) {
                    distances[i] = newDistance;
                    parent[i] = outerNode;
                }
            }
        }
    }
    cout << std::fixed << std::setprecision(2) << graph.weight << "\n";
    for (size_t i = 1; i < parent.size(); ++i) {
        if (i < parent[i]) {
            cout << i << " " << parent[i] << "\n";
        } else {
            cout << parent[i] << " " << i << "\n";
        }
    }
}

//double opt_mst(double (*dist)(const Node&, const Node&)) {
//    Graph graph;
//    vector<bool> inner(graph.nodes.size(), false);
//    inner[0] = true;
//    vector<uint32_t> parent(graph.nodes.size(), 0);
//    vector<double> distances(graph.nodes.size(), 0);
//    for (size_t i = 1; i < graph.nodes.size(); ++i) {
//        distances[i] = dist(graph.nodes[0], graph.nodes[i]);
//    }
//    distances[0] = std::numeric_limits<double>::infinity();
//    uint32_t numNode = 1;
//    while (numNode != graph.nodes.size()) {
//        /* add edge */
//        auto minElement = std::min_element(distances.begin(), distances.end());
//        double minDistance = *minElement;
//        uint32_t outerNode = (uint32_t)(minElement - distances.begin()),
//                innerNode = parent[outerNode];
//        graph.addEdge(outerNode, innerNode);
//        inner[outerNode] = true;
//        graph.weight += minDistance;
//        *minElement = std::numeric_limits<double>::infinity();
//        ++numNode;
//
//        /* update distances */
//        for (size_t i = 0; i < graph.nodes.size(); ++i) {
//            if (!inner[i]) {
//                /* for node[i] outside the graph */
//                double newDistance = dist(graph.nodes[i], graph.nodes[outerNode]);
//                if (newDistance < distances[i]) {
//                    distances[i] = newDistance;
//                    parent[i] = outerNode;
//                }
//            }
//        }
//    }
//    return graph.weight;
//}
//
//double vec_mst(vector<Node> nodes) {
//    double weight = 0;
//    vector<bool> inner(nodes.size(), false);
//    inner[0] = true;
//    vector<uint32_t> parent(nodes.size(), 0);
//    vector<double> distances(nodes.size(), 0);
//    for (size_t i = 1; i < nodes.size(); ++i) {
//        distances[i] = distance(nodes[0], nodes[i]);
//    }
//    distances[0] = std::numeric_limits<double>::infinity();
//    uint32_t numNode = 1;
//    while (numNode != nodes.size()) {
//        /* add edge */
//        auto minElement = std::min_element(distances.begin(), distances.end());
//        double minDistance = *minElement;
//        uint32_t outerNode = (uint32_t)(minElement - distances.begin());
//        inner[outerNode] = true;
//        weight += minDistance;
//        *minElement = std::numeric_limits<double>::infinity();
//        ++numNode;
//
//        /* update distances */
//        for (size_t i = 0; i < nodes.size(); ++i) {
//            if (!inner[i]) {
//                /* for node[i] outside the graph */
//                double newDistance = distance(nodes[i], nodes[outerNode]);
//                if (newDistance < distances[i]) {
//                    distances[i] = newDistance;
//                    parent[i] = outerNode;
//                }
//            }
//        }
//    }
//    return weight;
//}
