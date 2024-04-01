/* 
 * knapsack.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 10 Written.
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
using std::max;

#include "knapsack.h"

int knapsack(int C, const vector<int>& value, const vector<int>& weight) {
  vector<int> table(C+1, 0);
  for (int i = 1; i < (int)weight.size() + 1; ++i) {
    for (int j = C; j >= 0; --j) {
      if (weight[i-1] <= j) {
        table[j] = max(table[j], table[j-weight[i-1]]+value[i-1]);
      }
    }
  }
  return table[C];
}

int KS(int W, vector<int> wt, vector<int> val) {
  int n = wt.size();
  // Making and initializing dp array
  vector<int> dp(W+1, 0);
  for (int i = 1; i < n + 1; ++i)
    for (int w = W; w >= 0; w--)
      if (wt[i - 1] <= w)
        // Finding the maximum value
        dp[w] = max(dp[w],
                    dp[w - wt[i - 1]] + val[i - 1]);
  // Returning the maximum value of knapsack
  return dp[W];
}
