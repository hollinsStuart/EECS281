// Project identifier: 292F24D17A4455C1B5133EDD8C7CEAA0C9570A98
// Created by fs200 on 2023/11/5.

#ifndef PROJECT_1_COMMANDLINE_H
#define PROJECT_1_COMMANDLINE_H

#include <vector>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>
#include "getopt.h"

using std::cout, std::string, std::cerr, std::vector;

struct Options {
    bool verbose = false;
    bool haveFile = false;
    string fileName;
};  // Options{}

void printHelp();

void getMode(int argc, char* argv[], Options& options);

#endif //PROJECT_1_COMMANDLINE_H
