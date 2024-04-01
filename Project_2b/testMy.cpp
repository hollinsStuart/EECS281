#include <iostream>
#include <cmath>
#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
using std::vector;

#include "BinaryPQ.h"
#include "Eecs281PQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"
#include "UnorderedPQ.h"

using namespace std;

void testSorted(){
    vector<int> nums{1,14,8,24,51,30,67,27,3};
    SortedPQ<int, std::less<>> q(nums.begin(), nums.end());
    cout << q.top() << endl;
    q.push(4);
    q.push(424);
    cout << q.top() << endl;
    q.push(47);
    q.push(34);
    cout << q.top() << endl;;
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

void testBinary() {
    vector<int> nums{1,14,8,24,51,30,67,27,3};
    BinaryPQ<int, std::less<>> eq(nums.begin(), nums.end());
    cout << "Final result:\n";
    eq.printData();
    eq.printTree();
    cout << "Up 1!" << endl;
    eq.printTree();
    eq.pop();
    cout << "pop!" << endl;
    eq.printTree();
    eq.push(45);
    cout << "push!" << endl;
    eq.printTree();
    for (int i = 0; i < 4; ++i) {
        eq.pop();
    }
    while (!eq.empty()) {
        eq.printTree();
        eq.pop();
    }
    eq.printTree();
    cout << eq.size() << endl;
}

void testPairing(){
    vector<int> nums{1,14,8,24,51,30,67,27,3};
    PairingPQ<int, std::less<>> pairingPq(nums.begin(), nums.end());
    pairingPq.push(14);
    pairingPq.push(88);
    pairingPq.push(95);
    pairingPq.push(235);
    pairingPq.push(31);
    pairingPq.push(17);
    cout << "range-based constructed" << endl;
    PairingPQ pairingPq3 = pairingPq;
    cout << "operator= constructed" << endl;
    PairingPQ copiedPQ(pairingPq);
    cout << "operator() constructed" << endl;
    cout << "---------------------------------------\n()constructor:" << endl;
    cout << "copied top: " << copiedPQ.top() << ", size: " << copiedPQ.size() << endl;
    while(!copiedPQ.empty()) {
        cout << copiedPQ.top() << " ";
        copiedPQ.pop();
    }
    cout << endl << "copied size is: " << copiedPQ.size() << endl;
    cout << "---------------------------------------\noriginal:\n";
    cout << endl << "size is: " << pairingPq.size() << endl;
    while(!pairingPq.empty()) {
        cout << pairingPq.top() << " ";
        pairingPq.pop();
    }
    cout << endl << "size is: " << pairingPq.size() << endl;
    cout << "---------------------------------------\n=operator:\n";
    cout << "top: " << pairingPq3.top() << ", size: " << pairingPq3.size() << endl;
    pairingPq3.updatePriorities();
    cout << "updated! size is "<< pairingPq3.size() << endl;
    cout << pairingPq3.top() << " qqq " << endl;
    while(!pairingPq3.empty()) {
        cout << pairingPq3.top() << " ";
        pairingPq3.pop();
    }
    cout << endl << "copied size is: " << pairingPq3.size() << endl;
}

void testPairing2() {
    vector<int> nums{1,14,8,24,51,30,67,27,3};
    PairingPQ<int, std::greater<>> pairingPq(nums.begin(), nums.end());
    pairingPq.push(14);
    pairingPq.push(88);
    pairingPq.push(95);
    pairingPq.push(235);
    pairingPq.push(31);
    pairingPq.push(17);
    cout << "range-based constructed" << endl;
    PairingPQ pairingPq3 = pairingPq;
    cout << "operator= constructed" << endl;
    PairingPQ copiedPQ(pairingPq);
    cout << "operator() constructed" << endl;
    cout << "---------------------------------------\n()constructor:" << endl;
    cout << "copied top: " << copiedPQ.top() << ", size: " << copiedPQ.size() << endl;
    while(!copiedPQ.empty()) {
        cout << copiedPQ.top() << " ";
        copiedPQ.pop();
    }
    cout << endl << "copied size is: " << copiedPQ.size() << endl;
    cout << "---------------------------------------\noriginal:\n";
    cout << endl << "size is: " << pairingPq.size() << endl;
    while(!pairingPq.empty()) {
        cout << pairingPq.top() << " ";
        pairingPq.pop();
    }
    cout << endl << "size is: " << pairingPq.size() << endl;
    cout << "---------------------------------------\n=operator:\n";
    cout << "top: " << pairingPq3.top() << ", size: " << pairingPq3.size() << endl;
    pairingPq3.updatePriorities();
    cout << "updated! size is "<< pairingPq3.size() << endl;
    cout << pairingPq3.top() << " qqq " << endl;
    while(!pairingPq3.empty()) {
        cout << pairingPq3.top() << " ";
        pairingPq3.pop();
    }
    cout << endl << "copied size is: " << pairingPq3.size() << endl;
}

int main() {

//    testSorted();
//    testBinary();
    testPairing2();


    return 0;
}

