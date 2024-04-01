// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include "Node.h"

double distance(const MSTNode& a, const MSTNode& b) {
    if ((a.c == Category::Wild && b.c == Category::Safe) ||
        (b.c == Category::Wild && a.c == Category::Safe)) {
        return std::numeric_limits<double>::infinity();
    } else {
        return sqrt(((double)a.x - (double)b.x) * ((double)a.x - (double)b.x)
                    + ((double)a.y - (double)b.y) * ((double)a.y - (double)b.y));
    }
}

double distance(const Node& a, const Node& b) {
    return sqrt(((double)a.x - (double)b.x) * ((double)a.x - (double)b.x)
                + ((double)a.y - (double)b.y) * ((double)a.y - (double)b.y));
}
