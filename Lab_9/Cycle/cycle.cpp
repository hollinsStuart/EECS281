/* 
 * cycle.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 9 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "cycle.h"

using namespace std;

bool is_graph_cyclic(const vector<vector<int>> &adj_list) {
    vector<int> parent(adj_list.size(), -1);
    parent[0] = 0;
    queue<int> search;
    search.push(0);
    int curr = 0;
    while (!search.empty()) {
        for (auto &t: adj_list[curr]) {
            if (parent[t]!=-1) return false;
            search.push(t);
            parent[t] = curr;
        }
        curr = search.front();
        search.pop();
    }
  return false;
}
