/*
 * palindrome.h
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 1 Written.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef PALINDROME_H 
#define PALINDROME_H

struct Node {
  Node* prev;
  Node* next;
  char value;
};

bool isPalindrome(Node* start, Node* end);

#endif
