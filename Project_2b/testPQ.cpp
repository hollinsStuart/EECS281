// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

/*
 * Compile this test against your .h files to make sure they compile. We
 * suggest adding to this file or creating your own test cases to test your
 * priority queue implementations more thoroughly. If you do not call a
 * function from here, that template is not instantiated and that function is
 * NOT compiled! So for instance, if you don't add code here to call
 * updatePriorities, that function could later cause compiler errors that you
 * don't even know about.
 *
 * Our makefile will build an executable named testPQ if you type 'make
 * testPQ' or 'make alltests' (without the quotes). This will be a debug
 * executable.
 *
 * Notice that testPairing tests the range-based constructor but main and
 * testPriorityQueue do not. Make sure to test the range-based constructor
 * for other PQ types, and also test the PairingPQ-specific member functions.
 *
 * This is NOT a complete test of your priority queues. You have to add code
 * to do more testing!
 *
 * You do not have to submit this file, but it won't cause problems if you
 * do.
 */

#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
using std::vector;
#include <ctime>
#include <random>

#include "BinaryPQ.h"
#include "Eecs281PQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"
#include "UnorderedPQ.h"
#include "test.h"


// A type for representing priority queue types at runtime
enum class PQType {
    Unordered,
    Sorted,
    Binary,
    Pairing,
};

// These can be pretty-printed :)
std::ostream& operator<<(std::ostream& ost, PQType pqType) {
    switch (pqType) {
    case PQType::Unordered:
        return ost << "Unordered";
    case PQType::Sorted:
        return ost << "Sorted";
    case PQType::Binary:
        return ost << "Binary";
    case PQType::Pairing:
        return ost << "Pairing";
    }

    return ost << "Unknown PQType";
}


// Compares two int const* on the integers they point to
struct IntPtrComp {
    bool operator()(const int *a, const int *b) const { return *a < *b; }
};


// Test the primitive operations on a priority queue:
// constructor, push, pop, top, size, empty.
template <template <typename...> typename PQ>
void testPrimitiveOperations() {
    std::cout << "Testing primitive priority queue operations..." << std::endl;

    PQ<int> pq {};
    Eecs281PQ<int>& eecsPQ = pq;

    eecsPQ.push(3);
    eecsPQ.push(4);
    assert(eecsPQ.size() == 2);
    assert(eecsPQ.top() == 4);

    eecsPQ.pop();
    assert(eecsPQ.size() == 1);
    assert(eecsPQ.top() == 3);
    assert(not eecsPQ.empty());

    eecsPQ.pop();
    assert(eecsPQ.size() == 0);
    assert(eecsPQ.empty());

    // TODO: Add more testing here!

    std::cout << "testPrimitiveOperations succeeded!" << std::endl;
}


// Test that the priority queue uses its comparator properly. HiddenData
// can't be compared with operator<, so we use HiddenDataComp{} instead.
template <template <typename...> typename PQ>
void testHiddenData() {
    struct HiddenData {
        int data;
    };

    struct HiddenDataComp {
        bool operator()(const HiddenData &a, const HiddenData &b) const {
            // TODO: Finish this comparator
            return a.data < b.data;
        }
    };

    std::cout << "Testing with hidden data..." << std::endl;

    // TODO: Add code here to actually test with the HiddenData type.
    //  Consider writing this code in the style of testPrimitiveOperations
    //  above.
    HiddenData a{8};
    HiddenData b{90};
    HiddenData c{14};
    HiddenData d{367};
    HiddenData e{4};
    PQ<HiddenData, HiddenDataComp> hidden;
    hidden.push(a);
    hidden.push(b);
    hidden.push(c);
    hidden.push(d);
    hidden.push(e);

    std::cout << "testHiddenData succeeded!" << std::endl;
}


// Test the last public member function of Eecs281PQ, updatePriorities
template <template <typename...> typename PQ>
void testUpdatePriorities() {
    std::vector<int> data {
        1,
        5,
    };

    PQ<const int*, IntPtrComp> pq {};
    Eecs281PQ<const int*, IntPtrComp>& eecsPQ = pq;

    // NOTE: If you add more data to the vector, don't push the pointers
    //   until AFTER the vector stops changing size! Think about why.
    for (auto& datum : data) {
        eecsPQ.push(&datum);
    }

    // Change some element in data (which is pointed to by an element in pq).
    // This new value should be higher than any other so its address will
    // wind qt the top adter updatePriorities.
    auto& datum = data[0];
    datum = 10;
    eecsPQ.updatePriorities();
    assert(*eecsPQ.top() == 10);
    assert(eecsPQ.top() == &datum);

    // TODO: Add more testing here as you see fit.
}


// Test the pairing heap's range-based constructor, copy constructor,
// copy-assignment operator, and destructor
// TODO: Test other operations specific to this PQ type.
void testPairing() {
    std::cout << "Testing Pairing Heap separately..." << std::endl;

    {
        const std::vector<int> vec {
            1,
            0,
        };

        std::cout << "Calling constructors" << std::endl;
        // Range-based constructor
        PairingPQ<int> pairing1 { vec.cbegin(), vec.cend() };
        cout << "Range-based constructor: success" << endl;
        // Copy constructor
        PairingPQ<int> pairing2 { pairing1 };
        cout << "Copy constructor: success" << endl;
        // Copy-assignment operator
        PairingPQ<int> pairing3 {};
        pairing3 = pairing2;
        cout << "Copy-assignment constructor: success" << endl;

        // A reference to a PairingPQ<T> is a reference to an Eecs281PQ<T>.
        // Yay for polymorphism! We can therefore write:
        Eecs281PQ<int>& pq1 = pairing1;
        Eecs281PQ<int>& pq2 = pairing2;
        Eecs281PQ<int>& pq3 = pairing3;

        pq1.push(3);
        pq2.pop();
        assert(pq1.size() == 3);
        assert(not pq1.empty());
        assert(pq1.top() == 3);
        pq2.push(pq3.top());
        assert(pq2.top() == pq3.top());

        std::cout << "Basic tests done." << std::endl;

        // TODO: Add more code to test addNode, updateElt, etc.

        // That { above creates a scope, and our pairing heaps will fall out
        // of scope at the matching } below.
        std::cout << "Calling destructors" << std::endl;
    }

    std::cout << "testPairing succeeded!" << std::endl;
}

void testPairingYHC(){
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
    cout << "---------------------------------------\noriginal:";
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

void testLargePairing(){
    cout << "-----------------------------------------" << endl;
    cout << "testLargePairing..." << endl;
    vector<int> nums(5000);
    std::seed_seq seed = {114,514,7892};
    seed.generate(nums.begin(),nums.end());
    PairingPQ<int> q;
    for (auto i : nums) {
        q.addNode(i);
    }
    std::sort(nums.begin(), nums.end());
    cout << "PQ size is: " << q.size() << endl;
    while (!nums.empty()) {
        if (nums[nums.size()-1]!=q.top()) {
            cout << "not correct" << endl;
            assert(0);
        }
        nums.pop_back();
        q.pop();
    }
    cout << "large: success" << endl;
}

void testAddNode() {
    cout << "Testing: Add node\n";
//    vector<int> nums{1,14,8,24,51,30,67,27,3};
    PairingPQ<int, std::less<>> pairingPq;
    auto node1 = pairingPq.addNode(100);
    auto node2 = pairingPq.addNode(14);
    auto node3 = pairingPq.addNode(5);
    auto node4 = pairingPq.addNode(3);
    auto node5 = pairingPq.addNode(51);
    auto node6 = pairingPq.addNode(354);
    auto node7 = pairingPq.addNode(26);
    auto node8 = pairingPq.addNode(44);
    auto node9 = pairingPq.addNode(8);
    cout << "top is: " << pairingPq.top() << ", should be 354, size: " << pairingPq.size() << endl;
    cout << node1->getElt() << ' ';
    cout << node2->getElt() << ' ';
    cout << node3->getElt() << ' ';
    cout << node4->getElt() << ' ';
    cout << node5->getElt() << ' ';
    cout << node6->getElt() << ' ';
    cout << node7->getElt() << ' ';
    cout << node8->getElt() << ' ';
    cout << node9->getElt() << endl;
    pairingPq.updateElt(node4, 500);
    pairingPq.updateElt(node3, 40);
    cout << "top is: " << pairingPq.top() << ", should be 500, size: " << pairingPq.size() << endl;
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
    cout << "---------------------------------------\noriginal:";
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
    pairingPq.updatePriorities();
    pairingPq.updatePriorities();
    pairingPq.updatePriorities();
    pairingPq.updatePriorities();
    while(!pairingPq.empty()) {
        cout << pairingPq.top() << " ";
        pairingPq.pop();
    }
    cout << "size is: " << pairingPq.size() << endl;
}

void testUpdate(){
    cout << "-----------------------------------\nUpdate:" << endl;
    PairingPQ<int, std::less<>> pairingPq;
    pairingPq.addNode(100);
    pairingPq.addNode(14);
    pairingPq.addNode(5);
    pairingPq.addNode(3);
    pairingPq.addNode(51);
    auto node6 = pairingPq.addNode(354);
    pairingPq.addNode(26);
    pairingPq.addNode(44);
    pairingPq.addNode(8);
    pairingPq.updateElt(node6, 500);
    cout << "pairing 1: ";
    while(!pairingPq.empty()) {
        cout << pairingPq.top() << " ";
        pairingPq.pop();
    }
    cout << endl;
    PairingPQ<int, std::less<>> pairingPq2;
    pairingPq2.addNode(100);
    pairingPq2.addNode(14);
    pairingPq2.addNode(5);
    pairingPq2.addNode(3);
    pairingPq2.addNode(51);
    auto nodea6 = pairingPq2.addNode(354);
    pairingPq2.addNode(26);
    pairingPq2.addNode(44);
    pairingPq2.addNode(8);
    pairingPq2.updateElt(nodea6, 40);
    cout << "pairing 2: ";
    while(!pairingPq2.empty()) {
        cout << pairingPq2.top() << " ";
        pairingPq2.pop();
    }
    cout << endl;
}

// Run all tests for a particular PQ type.
template <template <typename...> typename PQ>
void testPriorityQueue() {
    testPrimitiveOperations<PQ>();
    testHiddenData<PQ>();
    testUpdatePriorities<PQ>();
}

// PairingPQ has some extra behavior we need to test in updateElement.
// This template specialization handles that without changing the nice
// uniform interface of testPriorityQueue.
template <>
void testPriorityQueue<PairingPQ>() {
    testAddNode();
    testLargePairing();
    testPrimitiveOperations<PairingPQ>();
    testHiddenData<PairingPQ>();
    testUpdatePriorities<PairingPQ>();
    testPairing();
    testPairingYHC();
}


int main() {
    const std::vector<PQType> types {
        PQType::Unordered,
        PQType::Sorted,
        PQType::Binary,
        PQType::Pairing,
    };

    std::cout << "PQ tester" << std::endl << std::endl;
    int idx { 0 };
    for (const auto &type : types) {
        std::cout << "  " << idx++ << ") " << type << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Select one: ";
    int choice {3};
//    std::cin >> choice;
    const PQType pqType = types.at(choice);

    std::cout << "Testing the " << pqType << " PQ...";

    // TODO: Add more cases to test other priority queue types.
    switch (pqType) {
        case PQType::Unordered:
            testPriorityQueue<UnorderedPQ>();
            break;
        case PQType::Sorted:
            testPriorityQueue<SortedPQ>();
            // std::vector<int> a{3,45,6,23,46,243,4576,745,547,235,123,64,7};
            // SortedPQ<int> pq(a.begin(), a.end(), std::less<int>());
            break;
        case PQType::Binary:
            testPrimitiveOperations<BinaryPQ>();
            testPriorityQueue<BinaryPQ>();
            testHiddenData<BinaryPQ>();
            break;
        case PQType::Pairing:
            simpleTest();
            fromScratch();
            cout << "------------------------\n";
            tryLeak();
//            testUpdate();
//            testPairing();
//            testAddNode();
//            testPrimitiveOperations<PairingPQ>();
//            cout << "primitive success!" << endl;
//            testPriorityQueue<PairingPQ>();
//            testHiddenData<PairingPQ>();
            testWithWeirdClass();
            break;
        default:
            std::cout << "Unrecognized PQ type " << pqType << " in main.\n"
                      << "You must add tests for all PQ types." << std::endl;
            return 1;
    }

    std::cout << "All tests succeeded.... or did them...." << std::endl;

    return 0;
}
