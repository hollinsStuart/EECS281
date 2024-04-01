// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/10.
//

#include "debug.h"

void printAllBackTraces(vector<vector<vector<char>>> &maps) {
    for (uint32_t i = 0; i < (uint32_t)maps.size(); ++i) {
        if (i==0) {
            cout << "// color ^\n";
        } else {
            cout << "// color " << (char)(96+i) << "\n";
        }
        printMap(maps[i]);
    }
    //cout << "------------------------\n";
}

void printMap(vector<vector<char>> &map) {
    for (vector<char>& row: map) {
        for (char c: row) {
            cout << c;
        }
        cout << "\n";
    }
}

void printDiscovered(vector<vector<vector<char>>> &maps, vector<vector<char>> &inputMap,
                     uint32_t height, uint32_t width) {
    // TODO: write the substitution methods
    cout << "No solution.\n" <<
            "Discovered:" << endl;
    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            if(!buttonNotPressed(maps, i, j)) {
                // not marked
                inputMap[i][j] = '#';
            } else {

            }
        }
    }
    printMap(inputMap);
}

void printSearchContainer(deque<Point>& sc) {
    cout << "Search Container: \n";
    if (sc.empty()) {
        cout << "empty\n";
        return;
    }
    for (auto it: sc) {
        cout << it << ", ";
    }
    cout << "sc end" << std::endl;
}

void printAsList(deque<Point> &container) {
    for (auto &i: container) {
        cout << i << "\n";
    }
}

/* make sure the container is empty when passed in */
deque<Point> findPath(vector<vector<vector<char>>> &maps,
                           deque<Point> &container, Point &p, uint32_t currentMapState) {
    uint32_t pos[3] = {currentMapState, p.row, p.col};    // store the coordinates in all back traces
    bool foundStart = false;
    while (!foundStart) {
        container.push_front(p);
        switch (maps[pos[0]][pos[1]][pos[2]]) {
            case 'N':
                --pos[1];
                break;
            case 'E':
                ++pos[2];
                break;
            case 'S':
                ++pos[1];
                break;
            case 'W':
                --pos[2];
                break;
            case ',':
                cerr << "position: " << pos[0] << pos[1] << pos[2];
                cerr << "\nwhy it is undiscovered?" << std::endl;
                exit(1);
            case '@':
                // found the start
                foundStart = true;
                break;
            default:
                // came from another color
                pos[0] = getMapNum(maps[pos[0]][pos[1]][pos[2]]);
        }
        p = Point{pos[0]==0 ? '^': (char)(96 + pos[0]), pos[1], pos[2]};
    }
    return container;
}

void printAsMap(vector<vector<vector<char>>> &maps, vector<vector<char>> &inputMap, deque<Point> &path,
                uint32_t height, uint32_t width) {
    // replace all the path
    Point current, prev;
    uint32_t pointArr[3] = {0, 0, 0};
    // start
    current = path.front();
    path.pop_front();
    pointToIndex(current, pointArr);
    maps[0][pointArr[1]][pointArr[2]] = '@';
    for (uint32_t i = 1; i < maps.size(); ++i) {
        maps[i][pointArr[1]][pointArr[2]] = '.';
    }

    /* mark the path */
    while(!path.empty()) {
        prev = current;
        current = path.front();
        path.pop_front();
        // from '@' to '?'
        pointToIndex(current, pointArr);    // update pointArr
        if (current.color != prev.color) {
            // jump
            maps[getMapNum(prev.color)][prev.row][prev.col] = '%';
            maps[pointArr[0]][pointArr[1]][pointArr[2]] = '@';
        } else {
            // on the same map
            maps[pointArr[0]][pointArr[1]][pointArr[2]] = '+';
        }
    }
    for (uint32_t i = 0; i < maps.size(); ++i) {
        maps[i][current.row][current.col] = '?';
    }

    /* replace undiscovered cells */
    char mapColor;
    for (uint32_t mapNum = 0; mapNum < maps.size(); ++mapNum) {
        if (mapNum == 0) {
            mapColor = '^';
        } else {
            mapColor = (char)(mapNum + 96);
        }
        for (uint32_t i = 0; i < height; ++i) {
            for (uint32_t j = 0; j < width; ++j) {
                if (maps[mapNum][i][j] == '@' || maps[mapNum][i][j] == '?'
                    || maps[mapNum][i][j] == '+' || maps[mapNum][i][j] == '%') {
                    // marked before
                } else {
                    // not marked
                    switch (inputMap[i][j]) {
                        case '.':
                            maps[mapNum][i][j] = '.';
                            break;
                        case '#':
                            maps[mapNum][i][j] = '#';
                            break;
                        case '@': break;
                        case '?': break;
                        case '^':
                            if (mapColor == '^') {
                                maps[mapNum][i][j] = '.';
                            }
                            else {
                                maps[mapNum][i][j] = '^';
                            }
                            break;
                        default:
                            if (inputMap[i][j] == mapColor || inputMap[i][j] == mapColor - 32) {
                                // door/button with the same color
                                maps[mapNum][i][j] = '.';
                            } else {
                                maps[mapNum][i][j] = inputMap[i][j];
                            }
                            break;
                    }
                }
            }
        }
    }
}

void pointToIndex(Point p, uint32_t* arr) {
    arr[0] = getMapNum(p.color);
    arr[1] = p.row;
    arr[2] = p.col;
}
