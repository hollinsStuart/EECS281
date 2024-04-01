// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/9/7.
//

#ifndef PROJECT_1_COMMANDLINE_H
#define PROJECT_1_COMMANDLINE_H

#include <vector>
#include <iostream>
#include <deque>
#include <stack>
#include <queue>
#include <string>
#include <cstdint>
#include <cstring>
#include "getopt.h"
#include "Zombie.h"

using std::cout, std::string, std::cerr, std::vector;

struct Options {
    bool verbose = false;
    bool statistics = false;
    uint32_t statistics_num = 0;
    bool median = false;    // true to print extra info
};  // Options{}

void printHelp();

void getMode(int argc, char* argv[], Options& options);

void printList(const deque<Zombie>& list);

#endif //PROJECT_1_COMMANDLINE_H
