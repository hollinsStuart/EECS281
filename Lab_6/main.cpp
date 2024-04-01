#include <iostream>
#include "two_pair_sums.h"

int main() {
    std::vector<int> nums{3, 4, 7, 1, 2, 8};
    std::vector<int> nothing{65 , 30, 7, 90, 1, 9, 8};
    two_pair_sums(nums, std::cout);
    std::cout << "nothing" << std::endl;
    two_pair_sums(nothing, std::cout);
    return 0;
}
