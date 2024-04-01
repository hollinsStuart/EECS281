#include <iostream>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include "knapsack.h"


int main() {
    std::vector<int> values = {
            360, 83, 59,  130, 431, 67, 230, 52,  93,  125, 670, 892, 600,
            38,  48, 147, 78,  256, 63, 17,  120, 164, 432, 35,  92,  110,
            22,  42, 50,  323, 514, 28, 87,  73,  78,  15,  26,  78,  210,
            36,  85, 189, 274, 43,  33, 10,  19,  389, 276, 312};

    std::vector<int> weights = {
            7,  0,  30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0,  36, 3,  8,  15,
            42, 9,  0,  42, 47, 52, 32, 26, 48, 55, 6,  29, 84, 2,  4,  18, 56,
            7,  29, 93, 44, 71, 3,  86, 66, 31, 65, 0,  79, 20, 65, 52, 13};

    std::vector<int> capacities = {850};
    cout << knapsack(capacities[0], values, weights) << endl;
    if (knapsack(capacities[0], values, weights) == 7534) std::cout << "Pass\n";
    else std::cout << "Fail\n";

    vector<int> profit = { 60, 100, 120 };
    vector<int> weight = { 10, 20, 30 };
    int W = 50;
    cout << knapsack(50, profit, weight) << endl;
    cout << KS(W, weight, profit) << endl;
    cout << KS(850, weights, values) << endl;


    return 0;
}
