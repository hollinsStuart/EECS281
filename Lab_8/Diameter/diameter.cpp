/*
* diameter.cpp
* University of Michigan, Ann Arbor
* EECS 281 Lab 8 Written.
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

#include "diameter.h"

using namespace std;

int diameter(const BinaryTreeNode* tree) {
    int left = findPair(tree->left);
    int right = findPair(tree->right);
    int children = max(left, right);
    int middle = findPair(tree);
    return max(middle, children);
}

int findDepth(const BinaryTreeNode* tree) {
    int left = 0, right = 0;
    if (tree->left == nullptr) left = 0;
    else {
        left = findDepth(tree->left);
    }
    if (tree->right == nullptr) right = 0;
    else {
        left = findDepth(tree->right);
    }
    return max(left, right) + 1;
}

int findPair(const BinaryTreeNode* tree) {
    int left = findDepth(tree->left);
    int right = findDepth(tree->right);
    return left+right;
}
