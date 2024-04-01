/*
 * replace_words.cpp
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 7 Written.
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

#include "replace_words.h"

using namespace std;

vector<string> replace_words(const vector<string>& prefixes,
                             const vector<string>& sentence) {
    vector<string> ans{sentence};
    // O(PN) naive approach
//    for (auto& word : ans) {
//        for (const auto& pre: prefixes) {
//            if (word.find(pre) == 0 && pre.length() < word.length()) {
//                word = pre;
//            }
//        }
//    }
    map<string, int> pre;
    for (int i = 0; i < prefixes.size(); ++i) {
        pre.insert({prefixes[i], i});
    } // O(PM)
    for (auto &item: ans) {
        for (int i = 0; i < item.size(); ++i) {
            string sub = item.substr(0, i);
            auto search = pre.find(sub);
            if (search != pre.end() && (search->first.length() < item.length())) {
                // found
                item = search->first;
            } // O(M)
        } // O(M)
    } // O(N)
    return ans;
}
