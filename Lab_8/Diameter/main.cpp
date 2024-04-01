//
// Created by fs200 on 2023/11/10.
//

#include <iostream>
#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "diameter.h"

using namespace std;

int main () {
    vector<int> v {14,12,13,5,7,9,10};
    v.insert(v.begin(), 0);
    for (auto i: v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
