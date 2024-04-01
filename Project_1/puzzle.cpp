// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/7.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <fstream>          // for I/O redirection
#include "commandLine.h"    // to proceed command line arguments
#include "helpers.h"        // helper functions
#include "debug.h"          // debugging functions

using std::cin, std::cout, std::cerr, std::endl, std::string, std::vector, std::deque;

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);  // speed up I/O

    /* ------- I/O redirection ------- */
    //std::ifstream in("test_read_map.txt");
    //std::ifstream in("small.txt");
    //std::ifstream in("spec-full-no.txt");
    //std::ifstream in("big.txt");
    //std::ifstream in("simple_colors.txt");
    //std::ifstream in("simplest.txt");
    //std::ifstream in("many_colors.txt"); // important for colors
    //std::ifstream in("many_colors_and_doors.txt"); // important for colors and doors
    //std::ifstream in("simple_test.txt");

    //cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    /* ------- I/O redirection ------- */

    Options options;
    getMode(argc, argv, options);

    int numColors = 0;
    uint32_t height, width;
    string junk;
    cin >> numColors >> height >> width;
    std::getline(cin, junk);    // remove '\n'
    if (numColors < 0 || numColors >26) {
        cerr << "Invalid numColors!" << endl;
        exit(1);
    }
    if (height < 1 || width < 1) {
        cerr << height << " " << width << endl;
        cerr << "Invalid height/width!" << endl;
        exit(1);
    }

    /* initialize maps */
    vector <vector<char>> inputMap (height, vector<char> (width));
    vector <vector<vector<char>>> backTraceMaps(
            numColors+1,
            vector<vector<char>>(height, vector<char>(width, ','))
            );

    /* search container */
    deque<Point> searchContainer;

    /* read map */
    string line;
    uint32_t inputLineNum = 0;
    while (getline(cin, line)) {
        if (inputLineNum==height) break;
        if (line[0] == '/' && line[1] == '/') {
            // it's a comment line
        } else {
            for (uint32_t j = 0; j < width; ++j) {
                inputMap[inputLineNum][j] = line[j];
            }
            ++inputLineNum;
        }
    }
    // the point is somewhere on the input map
    Point start = validMap(inputMap, numColors);
    searchContainer.push_back(start);
    Point currentState;
    // mark the initial state as discovered
    backTraceMaps[0][start.row][start.col] = '@';   // mark the start
    uint32_t currentStateMap = 0;       // stores the index of the current map
    bool foundPath = false;

    /* searching loop */
    while (!searchContainer.empty() && !foundPath) {
        if (options.mode == Mode::queue) {
            // queue
            currentState = (searchContainer.front());
            searchContainer.pop_front();
        } else {
            // stack
            currentState = searchContainer.back();
            searchContainer.pop_back();
        }
        //update the map current state is on
        currentStateMap = getMapNum(currentState.color);
//        cout << "CSM: " << currentStateMap << std::endl;
        // cout << "current state: "<< currentState << std::endl;
        // cout << "input map at CS: " << (inputMap[currentState.row][currentState.col]) << endl;
        // cout << countMarked(backTraceMaps, currentState.row, currentState.col) << " "
        // <<currentState.color<<inputMap[currentState.row][currentState.col]<<endl;
        // searchForPoints
        if (isButton(inputMap[currentState.row][currentState.col])
            //&& countMarked(backTraceMaps, currentState.row, currentState.col) == 1
            && currentState.color != inputMap[currentState.row][currentState.col] )
        {
            /* 1. standing on button
             * 2. it is marked only once on the backTraceMaps
             * 3. it has a different color than currentState, so the color will be changed
             * */
            // on an inactivated button, press and add new state
            // cout << "standing on button!" << std::endl;
            uint32_t newColor = getMapNum(inputMap[currentState.row][currentState.col]);
            // test if the button was pressed, if not, continue
            // printAllBackTraces(backTraceMaps);
            if (backTraceMaps[newColor][currentState.row][currentState.col] == ',') {
                searchContainer.push_back(Point{inputMap[currentState.row][currentState.col],
                                                currentState.row, currentState.col});
                // and mark the new state as discovered:
                //      color is current color (to mark where it is from)
                //      position is the current position

                backTraceMaps[newColor][currentState.row][currentState.col] = currentState.color;
            }
        } else {
            // not an inactive button, add new cells into the search container
            // and look for target & validity, in the order of N E S W
            if (currentState.row > 0){
                Point north = {inputMap[currentState.row - 1][currentState.col],
                               currentState.row - 1,
                               currentState.col};   // get the point, not a state
                switch (north.color) {
                    case '?':
                        backTraceMaps[currentStateMap][north.row][north.col] = 'S';
                        foundPath = true;
                        --currentState.row;
                        break;
                    case '#':
                        // a wall, do nothing
                        break;
                    default:
                        /* north is only a point (position), not a state.
                         * so the color of the state is identical with the current state */
                        tryPushNewState(north, currentState, searchContainer,
                                        backTraceMaps, Direction::north, currentStateMap);
                        break;
                }
            }
            if (currentState.col < width - 1){
                // there is an East cell
                Point east = {inputMap[currentState.row][currentState.col + 1],
                               currentState.row,
                               currentState.col + 1};   // get the point, not a state
                switch (east.color) {
                    case '?':
                        backTraceMaps[currentStateMap][east.row][east.col] = 'W';
                        foundPath = true;
                        ++currentState.col;
                        break;
                    case '#':
                        // a wall, do nothing
                        break;
                    default:
                        tryPushNewState(east, currentState, searchContainer,
                                        backTraceMaps, Direction::east, currentStateMap);
                        break;
                }
            }
            if (currentState.row < height - 1){
                Point south = {inputMap[currentState.row + 1][currentState.col],
                              currentState.row + 1,
                              currentState.col};   // get the point, not a state
                switch (south.color) {
                    case '?':
                        backTraceMaps[currentStateMap][south.row][south.col] = 'N';
                        foundPath = true;
                        ++currentState.row;
                        break;
                    case '#':
                        // a wall, do nothing
                        break;
                    default:
                        tryPushNewState(south, currentState, searchContainer,
                                        backTraceMaps, Direction::south, currentStateMap);
                        break;
                }
            }
            if (currentState.col > 0){
                Point west = {inputMap[currentState.row][currentState.col - 1],
                              currentState.row,
                              currentState.col - 1};   // get the point, not a state
                switch (west.color) {
                    case '?':
                        backTraceMaps[currentStateMap][west.row][west.col] = 'E';
                        foundPath = true;
                        --currentState.col;
                        break;
                    case '#':
                        // a wall, do nothing
                        break;
                    default:
                        tryPushNewState(west, currentState, searchContainer,
                                        backTraceMaps, Direction::west, currentStateMap);
                        break;
                }
            }
        } // search for new cells
    } // the search loop

    /* at this point, the current state is the location of the target */
    searchContainer.clear();    // release some memory

    if (foundPath) {
        searchContainer = findPath(backTraceMaps, searchContainer,
                                   currentState, currentStateMap);
        if (options.output == Output::list) {
            // print as a list
            for (auto &i: searchContainer) {
                cout << i << "\n";
            }
        } else {
            // print as a map
            printAsMap(backTraceMaps, inputMap, searchContainer, height, width);
            printAllBackTraces(backTraceMaps);
        }
    } else {
        // target not found, print discovered
        printDiscovered(backTraceMaps, inputMap, height, width);
    }

	return 0;
}

