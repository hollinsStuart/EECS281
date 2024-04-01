// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/10.
//

#include "helpers.h"

/* exit 1 if the map is not valid, return the starting point otherwise */
Point validMap(vector<vector<char>> &inputMap, int numColors) {
    bool findBegin = false;
    uint32_t endCount = 0;
    Point start;
    char c;

    for (uint32_t i = 0; i < (uint32_t)inputMap.size(); ++i) {
        for (uint32_t j = 0; j < (uint32_t)inputMap.begin()->size(); ++j) {
            c = inputMap[i][j];
            if (c == '@') {
                if (findBegin) {
                    std::cerr << "Two @'s!" << std::endl;
                    exit(1);
                }
                start.col = j;
                start.row = i;
                findBegin = true;
            } else if (c == '?') {
                ++endCount;
            } else if (c == '.' ||c == '#' || c == '^' ||
                        ((c>64) && (c<65+numColors)) ||
                        ((c>96) && (c<97+numColors))
                        ) {

            } else {
                /* invalid char */
                std::cerr << "bad char: "<< c << std::endl;
                exit(1);
            }
        }
    }

    if (!findBegin || (endCount != 1)) {
        std::cerr << "No start/end/Multiple ends!" << std::endl;
        exit(1);
    } // no start/end

    return start;
}

ostream& operator<<(ostream& os, const Point& p)
{
    cout << "(" << p.color << ", (" << p.row << ", " << p.col << "))";
    return os;
}

void tryPushNewState(Point& newPosition, Point& currentState,
                     deque<Point>& searchContainer,
                     vector<vector<vector<char>>> & backTraceMaps,
                     Direction direction,
                     uint32_t currentMapState) {
    if (backTraceMaps[currentMapState][newPosition.row][newPosition.col] == ',') {
        // not marked
        if (newPosition.color >= (int)'A' && newPosition.color <= (int)'Z') {   // door
            if ((newPosition.color + 32 == currentState.color)) {
                // a door with the same color, add a new state
                searchContainer.push_back(Point{currentState.color,
                                                newPosition.row,
                                                newPosition.col});
                // mark the point on the map (came from the South)
                // TODO: copy and paste the switch block
                switch (direction) {
                    case (Direction::north):
                        backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'S';
                        break;
                    case (Direction::east):
                        backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'W';
                        break;
                    case (Direction::south):
                        backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'N';
                        break;
                    case (Direction::west):
                        backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'E';
                        break;
                }
            }
        } else {
            // not a door
            // whether the non-door state has been discovered
            searchContainer.push_back(Point{currentState.color,
                                            newPosition.row,
                                            newPosition.col});
            switch (direction) {
                case (Direction::north):
                    backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'S';
                    break;
                case (Direction::east):
                    backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'W';
                    break;
                case (Direction::south):
                    backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'N';
                    break;
                case (Direction::west):
                    backTraceMaps[currentMapState][newPosition.row][newPosition.col] = 'E';
                    break;
            }
        }
    }
}

/* return true if not pressed/discovered  */
bool buttonNotPressed(vector<vector<vector<char>>> &backTraceMaps, uint32_t r, uint32_t c) {
    for (vector<vector<char>> &map: backTraceMaps) {
        if (map[r][c] != ',') return true;
    }
    return false;
}

int countMarked(vector<vector<vector<char>>> &backTraceMaps, uint32_t r, uint32_t c) {
    uint32_t ans = 0;
    for (int i = 0; i < (int)backTraceMaps.size(); ++i) {
        if (backTraceMaps[i][r][c] != ',') {
            cout << backTraceMaps[i][r][c] << "\n";
            ++ans;
        }
    }
    return ans;
}

bool isButton(char c) {
    if ((int)c == 94) return true;
    if ((int)c > 96 && (int)c < 123) return true;
    return false;
}

uint32_t getMapNum(char c) {
    return c == '^' ? 0 : c - 96;
}

