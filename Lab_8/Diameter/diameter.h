/*
* diameter.h
* University of Michigan, Ann Arbor
* EECS 281 Lab 8 Written.
* DO NOT SUBMIT TO GRADESCOPE.
* If submitted, this file will be ignored.
*/

#ifndef DIAMETER_H
#define DIAMETER_H

#include <map>

using std::pair;

struct BinaryTreeNode {
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  int value;
  explicit BinaryTreeNode(int n) : left{nullptr}, right{nullptr}, value{n} {}
};

int diameter(const BinaryTreeNode* tree);

int findDepth(const BinaryTreeNode* tree);

int findPair(const BinaryTreeNode* tree);


#endif