// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by hollins on 2023/11/22

#include <iostream>
using std::cout, std::cin, std::cerr, std::endl, std::getline;
#include <iomanip>
#include <algorithm>
using std::swap;
#include "commandLine.h"
#include "Node.h"
#include "MST.h"
#include "FastTSP.h"
#include "OptTSP.h"

int cnt = 0;

void testPerm(vector<int>path, uint32_t permLength) {
    if (permLength == path.size()) {
        for (auto i : path) {
            cout << i << " ";
        }
        cout << endl;
        ++cnt;
        return;
    }  // if ..complete path

    for (size_t i = permLength; i < path.size(); ++i) {
        swap(path[permLength], path[i]);
        testPerm(path, permLength + 1);
        swap(path[permLength], path[i]);
    }  // for ..unpermuted elements
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);  // speed up I/O
    Options options;
    getMode(argc, argv, options);
    switch (options.mode) {
        case Mode::NONE:
            cerr << "No Mode" << endl;
            exit(1);
        case Mode::MST:
            mst(distance);
            break;
        case Mode::FASTTSP:
            fast_tsp_insertion();
            break;
        case Mode::OPTTSP:
            OptTsp solve;
            solve.opt_start();
            solve.genPerms(1);
            solve.printBestPath();
            cerr << "p: " <<solve.p << ", r :" << solve.rejected << endl;
            break;
    }

    return 0;
}
