// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/10/3.
//

#ifndef P2A_PY_FUNCTORS_H
#define P2A_PY_FUNCTORS_H
#include "Zombie.h"
#include <deque>
#include <queue>
using std::priority_queue;
#include <vector>
using std::vector;


class zombieCompare {
public:
    bool operator()(const Zombie* a, const Zombie* b) const;
};

class zombieActive {
public:
    bool operator()(const Zombie* a, const Zombie* b) const;
    bool operator()(Zombie a, Zombie b) const;
};

class zombieActiveReversed {
public:
    bool operator()(const Zombie* a, const Zombie* b) const;
    bool operator()(Zombie a, Zombie b) const;
};

class zombieActiveLeft {
public:
    bool operator()(const Zombie* a, const Zombie* b) const;
};

class zombieActiveRight {
public:
    bool operator()(const Zombie* a, const Zombie* b) const;
};

void pushDeadZombie(priority_queue<Zombie*, vector<Zombie*>, zombieCompare> &,
                    priority_queue<Zombie*, vector<Zombie*>, zombieActiveLeft> &,
                    priority_queue<Zombie*, vector<Zombie*>, zombieActiveRight> &);

#endif //P2A_PY_FUNCTORS_H
