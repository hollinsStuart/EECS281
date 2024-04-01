// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/9/30.
//

#ifndef P2A_PY_ZOMBIE_H
#define P2A_PY_ZOMBIE_H

#include <iostream>
using std::cout, std::endl, std::cerr;
#include <string>
using std::string;
#include <cstdint>
#include <deque>
using std::deque;

class Zombie {
public:
    string name;
    uint32_t distance;
    uint32_t speed;
    uint32_t health;
    uint32_t active;

    Zombie();
    Zombie(const Zombie&);
    Zombie(string, uint32_t, uint32_t, uint32_t);
    ~Zombie() = default;
};

#endif //P2A_PY_ZOMBIE_H
