// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include <iostream>
using std::cout, std::cin, std::cerr, std::endl, std::getline;
#include <iomanip>
#include <algorithm>
using std::swap;
#include "OptTSP.h"
#include "FastTSP.h"
//#include <iomanip>
//using std::setw;

OptTsp::OptTsp() = default;

void OptTsp::opt_start() {
    bestPath = {0, 0};    // 0, ..., 0
    uint32_t newParentIndex{};    // node num | index in the bestPath
    /* find node with the shortest distance from the bestPath*/
    for (uint32_t i = 1; i < (uint32_t)graph.nodes.size(); ++i) {
        /* for node[i] */
        double deltaDistance = std::numeric_limits<double>::infinity();
        for (size_t j = 0; j < bestPath.size() - 1; ++j) {
            double leftDistance = distance(graph.nodes[bestPath[j]], graph.nodes[i]),
                    rightDistance = distance(graph.nodes[bestPath[j+1]], graph.nodes[i]);
            /* distance with bestPath[j], bestPath[j+1] */
            double curDistance = leftDistance + rightDistance
                                 - distance(graph.nodes[bestPath[j]], graph.nodes[bestPath[j+1]]);
            if (curDistance < deltaDistance) {
                deltaDistance = curDistance;
                newParentIndex = (uint32_t)j;
            }
        }
        bestPath.insert(bestPath.begin()+newParentIndex+1, i);
    }
    bestCost = 0;
    for (size_t i = 0; i < bestPath.size() - 1; ++i) {
        bestCost += distance(graph.nodes[bestPath[i]], graph.nodes[bestPath[i+1]]);
    }
    bestPath.pop_back();
    curPath = bestPath;
    curCost = 0;
}

void OptTsp::genPerms(uint32_t permLength) {
    if (permLength == bestPath.size()) {
        double ending = distance(graph.nodes[0],
                                 graph.nodes[curPath[curPath.size()-1]]);
        curCost += (ending);
        if (curCost < bestCost) {
            bestPath = curPath;
            bestCost = curCost;
        }
        curCost -= (ending );
        return;
    }  // if ..complete path

    if (!promising(permLength)) return;

    for (size_t i = permLength; i < curPath.size(); ++i) {
        swap(curPath[permLength], curPath[i]);
        double newEdgeCost = permLength < 1? 0:
                distance(graph.nodes[curPath[permLength]], graph.nodes[curPath[permLength-1]]);
        curCost += newEdgeCost;
        genPerms(permLength + 1);
        curCost -= newEdgeCost;
        swap(curPath[permLength], curPath[i]);
    }  // for ..unpermuted elements
}


/* mst and arms algorithm here */
bool OptTsp::promising(uint32_t permLength)  {
    if (curCost > bestCost) {
        ++rejected;
        return false; }
    if (permLength + 5 > bestPath.size()) { ++p;return true; }
    double leftArm{std::numeric_limits<double>::infinity()},
           rightArm{std::numeric_limits<double>::infinity()};   // should be the two shortest arms
    for (size_t i = permLength; i < curPath.size(); ++i) {
        /* for [i] outside the graph */
        leftArm = std::min(distance(graph.nodes[curPath[0]], graph.nodes[curPath[i]]), leftArm);
        rightArm = std::min(distance(graph.nodes[curPath[permLength-1]], graph.nodes[curPath[i]]), rightArm);
    }
    if (curCost + leftArm + rightArm + mst(permLength) < bestCost) {
        ++p;
        return true;
    }
    ++rejected;
    return false;
}

double OptTsp::mst(uint32_t permLength) const {
    double weight = 0;
    /* start at permlength, end at size()-1 */
    uint32_t Size = (uint32_t)curPath.size() - permLength;
    vector<bool> inner(Size, false);
    inner[0] = true;
    vector<uint32_t> parent(Size, 0);
    vector<double> distances(Size, 0);
    for (size_t i = 1; i < Size; ++i) {
        distances[i] = distance(graph.nodes[curPath[permLength+i]], graph.nodes[curPath[permLength]]);
    }
    distances[0] = std::numeric_limits<double>::infinity();
    uint32_t numNode = 1;
    while (numNode != Size) {
        /* add edge */
        double minDistance = std::numeric_limits<double>::infinity();
        uint32_t minIndex = 0;
        for (uint32_t j = 0; j < distances.size(); ++j) {
            if (distances[j] < minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }
        inner[minIndex] = true;
        weight += minDistance;
        distances[minIndex] = std::numeric_limits<double>::infinity();
        ++numNode;

        /* update distances */
        for (size_t i = 0; i < Size; ++i) {
            if (!inner[i]) {
                /* for node[i] outside the graph */
                double newDistance = distance(graph.nodes[curPath[permLength + i]],
                                              graph.nodes[curPath[minIndex + permLength]]);
                if (newDistance < distances[i]) {
                    distances[i] = newDistance;
                    parent[i] = minIndex;
                }
            }
        }
    }
    return weight;
}

void OptTsp::printBestPath() const {
    cout << std::fixed << std::setprecision(2) << bestCost << "\n";
    for (unsigned int i : bestPath) {
        cout << i << " ";
    }
    cout << "\n";
}


