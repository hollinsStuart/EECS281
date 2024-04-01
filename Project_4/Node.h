// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include <limits>
#include <valarray>

#ifndef PROJECT_4_NODE_H
#define PROJECT_4_NODE_H

enum class Category {
    Safe, Border, Wild
};

class MSTNode {
public:
    MSTNode(): x(0), y(0), c(Category::Safe) {};
    MSTNode(int X, int Y): x(X), y(Y) {
        if (x < 0 && y < 0) {
            c = Category::Wild;
        } else if ((x == 0 && y <= 0) || (y == 0 && x <= 0)) {
            c = Category::Border;
        } else {
            c = Category::Safe;
        }
    }
    ~MSTNode() = default;

    int x;
    int y;
    Category c;

};

class Node {
public:
    Node(): x(0), y(0) {};
    Node(int X, int Y): x(X), y(Y) {};
    ~Node() = default;

    int x;
    int y;
};


double distance(const MSTNode& a, const MSTNode& b);

double distance(const Node& a, const Node& b);

#endif //PROJECT_4_NODE_H
