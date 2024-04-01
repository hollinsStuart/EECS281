// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#ifndef PROJECT_1_COMMANDLINE_H
#define PROJECT_1_COMMANDLINE_H

#include <vector>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>
#include "getopt.h"

using std::cout, std::string, std::cerr, std::vector;

enum class Mode {
    NONE, MST, FASTTSP, OPTTSP
};

struct Options {
    Mode mode = Mode::NONE;
};  // Options{}

void printHelp();

void getMode(int argc, char* argv[], Options& options);

#endif //PROJECT_1_COMMANDLINE_H
