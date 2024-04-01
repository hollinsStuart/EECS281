/* 
 * two_pair_sums.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 6 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "two_pair_sums.h"

using namespace std;

void two_pair_sums(const vector<int>& nums, ostream& os) {
    map<int, vector<int>> m;    // sum, pair
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i+1; j < nums.size(); ++j) {
            if (nums[i] == nums[j]) continue;
            int sum = nums[i] + nums[j];
            auto it = m.find(sum);
            if (it != m.end() && !(nums[i] == it->second[0] || nums[i] == it->second[1])) {
                // found the value
                it->second.push_back(nums[i]);
                it->second.push_back(nums[j]);
            } else {
                m.insert({sum, vector<int>{nums[i], nums[j]}});
            }
        }
    }
    for (auto it: m) {
        if (it.second.size()==4) {
            os << "(" << it.second[0] << ", " << it.second[1] << ") and ("
               << it.second[2] << ", " << it.second[3] << ")" << endl;
        }
    }
}
