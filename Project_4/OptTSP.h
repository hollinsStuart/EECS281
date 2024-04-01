// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include <vector>
using std::vector;
#include <cstdint>
#include "Node.h"
#include "Graph.h"

#ifndef PROJECT_4_OPTTSP_H
#define PROJECT_4_OPTTSP_H

class OptTsp {
public:
    /* read in the graph and get the starting bound */
    OptTsp();
    ~OptTsp() = default;

    void opt_start();

    /* find the best path */
//    void findBest();

    /* recursive function call */
    void genPerms(uint32_t permLength);

    void printBestPath() const;
    long long p{};
    long long rejected{};
private:

    bool promising(uint32_t permLength) ;

    /* generate a mst for the unconnected nodes, return its length */
    double mst(uint32_t permLength) const;

    Graph graph;
    vector<uint32_t> bestPath;
    double bestCost{};
    vector<uint32_t> curPath;
    double curCost{};


};

//template <typename T>
//void genPerms(vector<T> &path, size_t permLength) {
//    if (permLength == path.size()) {
//        // Do something with the path
//        /* curCost += (closing edge) [from end to vertex 0]
//         * check if better
//         *      update things
//         * curCost -= (closing edge) [from end to vertex 0]
//         * get the total length of the current length and compare it
//         * with the best path for now */
//        return;
//    }  // if ..complete path
//
//    if (!promising(path, permLength)) {
//        return;
//    }  // if ..not promising
//
//    for (size_t i = permLength; i < path.size(); ++i) {
//        swap(path[permLength], path[i]);
//        // currCost += (cost of new edge)
//        genPerms(path, permLength + 1);
//        // currCost -= (cost of new edge)
//        swap(path[permLength], path[i]);
//    }  // for ..unpermuted elements
//}  // genPerms()

#endif //PROJECT_4_OPTTSP_H
