// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/10.
//

#ifndef PROJECT_1_DEBUG_H
#define PROJECT_1_DEBUG_H

#include <vector>
#include <deque>
#include <iostream>
#include "helpers.h"

using std::vector, std::deque, std::cout, std::endl;

void printAllBackTraces(vector<vector<vector<char>>> &);

void printMap(vector<vector<char>> &);

void printDiscovered(vector<vector<vector<char>>> &, vector<vector<char>> &,
                     uint32_t, uint32_t);

void printSearchContainer(deque<Point> &);

void printAsList(deque<Point> &);

void printAsMap(vector<vector<vector<char>>> &, vector<vector<char>> &, deque<Point> &,
                uint32_t, uint32_t);

deque<Point> findPath(vector<vector<vector<char>>> &,
                      deque<Point> &, Point &, uint32_t);

void pointToIndex(Point, uint32_t* );

#endif //PROJECT_1_DEBUG_H
