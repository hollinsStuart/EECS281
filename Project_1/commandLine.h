// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/7.
//

#ifndef PROJECT_1_COMMANDLINE_H
#define PROJECT_1_COMMANDLINE_H

#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>
#include "getopt.h"

using std::cout, std::string, std::cerr, std::vector;

enum class Mode
{
    stack, queue, none
};

enum class Output
{
    map, list, none
};

enum class Direction
{
    north, east, south, west
};

struct Options {
    Mode mode = Mode::none;
    Output output = Output::none;
};  // Options{}

void printHelp();

void getMode(int argc, char* argv[], Options& options);

#endif //PROJECT_1_COMMANDLINE_H
