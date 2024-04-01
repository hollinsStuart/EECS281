// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/10.
//

#ifndef PROJECT_1_HELPERS_H
#define PROJECT_1_HELPERS_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <deque>
#include <algorithm>
#include "commandLine.h"

using std::vector, std::deque, std::find, std::cout, std::ostream;

struct Point {
    char color = '^';
    uint32_t row = 0;
    uint32_t col = 0;

    inline Point& operator=(const Point& a) = default;

    bool operator == (const Point &c) const
    {
        if (color == c.color && row == c.row && col == c.col)
            return true;
        return false;
    }

};

ostream& operator<<(ostream& os, const Point& p);

Point validMap(vector<vector<char>> &inputMap, int numColors);

void tryPushNewState(Point& newPosition, Point& currentState,
                     deque<Point>& searchContainer,
                     vector<vector<vector<char>>> & backTraceMaps,
                     Direction d,
                     uint32_t a);

bool buttonNotPressed(vector<vector<vector<char>>> & backTraceMaps, uint32_t r, uint32_t c);

int countMarked(vector<vector<vector<char>>> &backTraceMaps, uint32_t r, uint32_t c);

bool isButton(char c);

uint32_t getMapNum(char c);

#endif //PROJECT_1_HELPERS_H
