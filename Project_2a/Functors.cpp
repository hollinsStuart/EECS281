// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/10/3.
//

#include "Functors.h"

bool zombieCompare::operator()(const Zombie* a, const Zombie* b) const {
    if ((int)(a->distance/a->speed) == (int)(b->distance/b->speed)) {
        if (a->health == b->health) {
            return a->name > b->name;
        } else {
            return a->health > b->health;
        }
    } else {
        return (int)a->distance/a->speed > (int)b->distance/b->speed;
    }
}

bool zombieActive::operator()(const Zombie* a, const Zombie* b) const {
    return a->active < b->active;
}

bool zombieActive::operator()(const Zombie a, const Zombie b) const {
    if (a.active == b.active) {
        return a.name < b.name;
    } else {
        return a.active < b.active;
    }
}

bool zombieActiveReversed::operator()(const Zombie* a, const Zombie* b) const {
    return a->active > b->active;
}

bool zombieActiveReversed::operator()(const Zombie a, const Zombie b) const {
    if (a.active == b.active) {
        return a.name < b.name;
    } else {
        return a.active > b.active;
    }
}

bool zombieActiveLeft::operator()(const Zombie* a, const Zombie* b) const {
    return a->active < b->active;
}

bool zombieActiveRight::operator()(const Zombie* a, const Zombie* b) const {
    return a->active > b->active;
}

void pushDeadZombie(priority_queue<Zombie*, vector<Zombie*>, zombieCompare> &list,
                    priority_queue<Zombie*, vector<Zombie*>, zombieActiveLeft> &left,
                    priority_queue<Zombie*, vector<Zombie*>, zombieActiveRight> &right) {
    if (left.empty() && right.empty()) {
        left.push(list.top());
    } else if (!left.empty() && right.empty()) {
        left.push(list.top());
        right.push(left.top());
        left.pop();
    } else {
        uint32_t num = list.top()->active;
        if (left.size() == right.size()) {
            if (num < right.top()->active) {
                left.push(list.top());
            } else {
                right.push(list.top());
                left.push(right.top());
                right.pop();
            }
        } else {
            if (num < right.top()->active) {
                left.push(list.top());
                right.push(left.top());
                left.pop();
            } else {
                right.push(list.top());
            }
        }
    }
    list.pop();
}
