// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#ifndef PROJECT_4_MST_H
#define PROJECT_4_MST_H

#include <vector>
using std::vector;
#include <iostream>
using std::cout, std::cin, std::cerr, std::endl, std::getline;
#include "Node.h"

void mst(double (*dist)(const MSTNode&, const MSTNode&));
double opt_mst(double (*dist)(const Node&, const Node&));
double vec_mst(vector<Node> nodes);
#endif //PROJECT_4_MST_H
