#ifndef AVL_LAB_H
#define AVL_LAB_H

#include <iostream>

// used for printing the trees
#include <vector>
#include <utility>
#include <functional>

// LAB 8: Ro-Tater Tots
// INSTRUCTIONS:
// finish the implementations for:
// AVL::Node* AVL::rotate_right(AVL::Node* node)
// AVL::Node* AVL::rotate_left(AVL::Node* node)
// AVL::Node* AVL::insert_node(AVL::Node*, int datum)
// IDENTIFIER: EAA16B5C3724FBFD78F132136AABBBBA4952E261

// Modify the parts that say YOUR CODE HERE (starting at line 209).
// The rest has been done for you.

// You may make any changes you like to this file.


// probably useful
int max(int x, int y) {
    return x > y ? x : y;
}

size_t max_size_t(size_t x, size_t y) {
    return x > y ? x : y;
}

class AVL {
public:
    struct Node {
        int datum;
        int height;
        Node* left;
        Node* right;
        int left_height() const {
            return left ? left->height : 0;
        }
        int right_height() const {
            return right ? right->height : 0;
        }
        int balance() const {
            return left_height() - right_height();
        }
        // Whenever the height of its children change, call
        // this function to recalculate the height of this node,
        // the parent.
        void fix_height() {
            height = 1 + max(left_height(), right_height());
        }
    };
    void insert(int datum);
    const Node* search(int datum, bool print_path = false) const;
    ~AVL();
    AVL::Node* check_and_balance(AVL::Node* node);


    // a debugging method that will print the tree for you
    // (use it to inspect small trees, if you want)
    void debug_print_tree() {
        debug_print_node(0, root);
    }

    // NOTE: this function is really complicated
    // don't worry too much about how it works
    // TODO: support 3+ digit numbers
    void print_diagram() {
        struct pos {
            size_t depth;
            int parent_dir;
        };
        std::vector<std::pair<int, pos>> points;
        std::function<void(Node*, pos p)> traverse_depth = [&](Node* n, pos p) {
            if (n == nullptr) {
                return;
            }
            traverse_depth(n->left, { p.depth + 1, 1 });
            points.push_back(std::pair<int, pos>({ n->datum, p }));
            traverse_depth(n->right, { p.depth + 1, -1 });
        };
        traverse_depth(root, { 0, 0 });
        // points is now filled
        size_t width = 2 * points.size();
        size_t height = 0;
        for (auto & point : points) {
            height = max_size_t(height, point.second.depth);
        }
        height *= 2;
        height++;
        // now, we can build the buffer:
        std::vector<std::vector<char>> buffer(width, std::vector<char>(height, ' '));
        // add the numbers
        for (size_t i = 0; i < points.size(); i++) {
            int n = points[i].first;
            size_t d = points[i].second.depth;
            buffer[2 * i + 1][d * 2] = char((n % 10) + '0');
            if (n >= 10) {
                // note: will truncate 3+ digit numbers to their last 2 digits
                buffer[2 * i + 0][d * 2] = char((n / 10) % 10 + '0');
            }
        }
        // add the corner edges
        for (size_t i = 0; i < points.size(); i++) {
            size_t d = points[i].second.depth;
            int dir = points[i].second.parent_dir;
            if (dir == 0) {
                continue; // root
            }
            if (points[i + (size_t)dir].second.depth == d - 1) {
                // adjacent parent
                buffer[2 * i + (dir > 0 ? 2 : 0)][d * 2 - 1] = (dir > 0 ? '/' : '\\');
            } else {
                size_t c = 2 * i + (size_t)(dir > 0 ? 2 : -1);
                buffer[c][d * 2 - 1] = (dir > 0 ? '/' : '\\');
                buffer[c + (size_t)dir][d * 2 - 2] = '-';
                for (size_t j = i + (size_t)(2 * dir); points[j].second.depth != d - 1; j += (size_t)dir) {
                    buffer[2 * j][d * 2 - 2] = '-';
                    buffer[2 * j + 1][d * 2 - 2] = '-';
                }

            }
        }
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                std::cout << buffer[x][y];
            }
            std::cout << std::endl;
        }
    }

    size_t getSize() const {return size;}
private:
    Node* root = nullptr;
    size_t size = 0;

    // insert_node returns the increase in height for the provided tree
    Node* insert_node(Node* node, int datum);

    // search_node returns the node, or nullptr
    const Node* search_node(const Node* node, int datum, bool print_path) const;

    // these return the new top node after rotation
    Node* rotate_left(Node* node);
    Node* rotate_right(Node* node);
    void destroy_node(Node* node);

    void debug_print_node(int depth, Node* node) {
        if (node == nullptr) {
            return;
        }
        debug_print_node(depth + 1, node->left);
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << node->datum << std::endl;
        debug_print_node(depth + 1, node->right);
    }

};

const AVL::Node* AVL::search(int datum, bool print_path) const {
    // just a regular BST search
    return search_node(root, datum, print_path);
}

// search_node searches for 'datum' in the subtree rooted at 'node'.
// if the node cannot be found, it returns nullptr.
const AVL::Node* AVL::search_node(const AVL::Node* node, int datum, bool print_path) const {
    if (node == nullptr) {
        if (print_path) {
            std::cout << "M" << std::endl;
        }
        return nullptr; // not found (no node here)
    }
    if (node->datum == datum) {
        // found the target
        if (print_path) {
            std::cout << "X" << std::endl;
        }
        return node;
    }
    if (datum < node->datum) {
        // left subtree, since smaller than current node
        if (print_path) {
            std::cout << "L";
        }
        return search_node(node->left, datum, print_path);
    } else {
        if (print_path) {
            std::cout << "R";
        }
        // right subtree, since larger than current node
        return search_node(node->right, datum, print_path);
    }
}

void AVL::insert(int datum) {
    root = insert_node(root, datum);
}

// insert_node returns the new root of this subtree after inserting datum.
// if datum already exists in the tree, the copy is inserted to its right.
AVL::Node* AVL::insert_node(AVL::Node* node, int datum) {
    if (node == nullptr) {
        // at a leaf position in the tree, so create a new node
        ++size;
        return new Node{ datum, 1, nullptr, nullptr }; // it has height 1
    }
    if (datum < node->datum) {
        node->left = insert_node(node->left, datum);
        node->fix_height(); // remember to fix the height of a node after modifying its children
        node->left->fix_height();
        node = check_and_balance(node);
    } else {
        node->right = insert_node(node->right, datum);
        node->fix_height(); // remember to fix the height of a node after modifying its children
        node->right->fix_height();
        node = check_and_balance(node);
    }
    ++size;
    return node;
}

// rotate_left performs a left rotation; it returns the new 'root' of the rotated subtree
// (remember to update the heights of nodes!)
// you may assume that it has a right child
AVL::Node* AVL::rotate_left(AVL::Node* node) {
//    std::cout << "RL: " << node->datum << std::endl;
    Node* b = node->right;
    Node* temp = node->right->left;
    b->left = node;
    node->right = temp;
    node->fix_height();
    b->fix_height();
    return b;
}

// rotate_right performs a right rotation; it returns the new 'root' of the rotated subtree
// (remember to update the heights of nodes!)
// you may assume that it has a left child
AVL::Node* AVL::rotate_right(AVL::Node* node) {
//    std::cout << "RR: " << node->datum << std::endl;
    Node* b = node->left;
    Node* temp = node->left->right;
    b->right = node;
    node->left = temp;
    node->fix_height();
    b->fix_height();
    return b;
}

AVL::~AVL() {
    destroy_node(root);
}

void AVL::destroy_node(AVL::Node* node) {
    if (node == nullptr) {
        return;
    }
    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
}

AVL::Node* AVL::check_and_balance(AVL::Node *node) {
//    std::cout << "CB: " << node->datum << std::endl;
    if (node->balance() > 1) {
        if (node->left->balance() < 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    } else if (node->balance() < -1) {
        if (node->right->balance() > 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    return node;
}

#endif /* AVL_LAB_H */
