#include <vector>
#include <algorithm>
#include <iostream>
using std::cout, std::endl;
using std::vector, std::swap;

void sort012(vector<int>& nums) {
    int num2s = 0;
    int num0s = 0;
    for (int i = 0; i < (int)nums.size(); ++i) {
        if ((i+num2s) == (int)nums.size()) break;        
        if (nums[i]==0) {
            swap(nums[i], nums[num0s]);
            ++num0s;
            i=num0s-1;
        } else if (nums[i]==2) {
            swap(nums[i], nums[nums.size()-1-num2s]);
            ++num2s;
            --i;
        }
    }
    for (int &i: nums) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {0,2,1,2,1,2,0,1,2,0,0,1,0,2,1,1};
    vector<int> sdhort = {1,2,0,0,2};
    sort012(nums);
    sort012(sdhort);
    vector<int> zeros(10,0);
    sort012(zeros);
    vector<int> twos(10,2);
    sort012(twos);
    vector<int> ones(10,1);
    sort012((ones));
    vector<int> ow{2,0,2,0,2,0,2,0,2,2,2,0,0,0,2};
    sort012(ow);
    vector<int> oo{1,1,1,1,0,0,1,0,0,1,1,1};
    sort012(oo);
    vector<int>ot{1,2,1,2,2,2,2,2,1,1,1,2,1,2,2,1,1};
    sort012(ot);
    sort012(nums);

}
