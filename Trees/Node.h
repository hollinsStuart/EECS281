//
// Created by fs200 on 2023/11/2.
//

#ifndef TREES_NODE_H
#define TREES_NODE_H

template<typename T>
class Node {
public:
    T value;
    Node* left;
    Node* right;
    int height{}; // for AVL tree

    Node() = default;
    explicit Node(T &val): value (val), left(nullptr), right(nullptr), height(0) {};
    ~Node() = default;
};


#endif //TREES_NODE_H
