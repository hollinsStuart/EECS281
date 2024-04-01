// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/9/30.
//

#include "Zombie.h"

Zombie::Zombie(): name{""}, distance{0}, speed{0}, health{0}, active{1} {}

Zombie::Zombie(const Zombie& z): name{z.name}, distance{z.distance}, speed{z.speed}
                                , health{z.health}, active{z.active} {}

Zombie::Zombie(string Name, uint32_t Distance, uint32_t Speed, uint32_t Health):
        name{Name}, distance{Distance}, speed{Speed}, health{Health}, active{1} {}

