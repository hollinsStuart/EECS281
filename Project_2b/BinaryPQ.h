// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include <cmath>
#include <iostream>
using std::cout, std::endl;
#include "Eecs281PQ.h"
using std::size_t;

// A specialized version of the priority queue ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function, or verify that it is already done
        data.push_back(TYPE());
    } // BinaryPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function
        data.push_back(TYPE());
        while(start != end) {
            data.push_back(*start);
            ++start;
        }
        BinaryPQ::updatePriorities();
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() = default; // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        for (size_t i = (size_t)data.size() / 2; i > 0; --i) {
            fixDown(i);
        }
    } // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        // TODO: Implement this function.
        data.push_back(val);
        this->fixUp(data.size()-1);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        data[1] = data[data.size()-1];
        data.pop_back();
        fixDown(1);
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function.
        return data[1];
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function. Might be very simple,
        //       depending on your implementation.
        return data.size() - 1;
    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function. Might be very simple,
        //       depending on your implementation
        return data.size()==1;
    } // empty()

    /* test */
    void printData() {
        for (auto &i: data) {
            cout << i << " ";
        }
        cout << endl;
    }

    void printTree() {
        for (int i = 1; i < (int)data.size(); i*=2) {
            if (i==1) cout << "       ";
            if (i==2) cout << "     ";
            if (i==4) cout << "  ";
            for (int j = i; j < 2*i && j < (int)data.size(); ++j) {
                cout << data[j] << " ";
            }
            cout << endl;
        }
    }

private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // TODO: Add any additional member functions you require here.
    //       For instance, you might add fixUp() and fixDown().

    void fixDown(std::size_t pos) {
        size_t parentIndex = pos;
        size_t leftChildIndex = parentIndex * 2;
        while (leftChildIndex < data.size()) {
            size_t largerChildIndex = leftChildIndex;
            size_t rightChildIndex = parentIndex * 2 + 1;
            if (rightChildIndex < data.size()) {
                largerChildIndex = this->compare(data[leftChildIndex], data[rightChildIndex]) ?
                                   rightChildIndex : leftChildIndex;
            }
            if (this->compare(this->data[parentIndex], this->data[largerChildIndex])) {
                TYPE temp = this->data[largerChildIndex];
                this->data[largerChildIndex] = this->data[parentIndex];
                this->data[parentIndex] = temp;
            }
            parentIndex = largerChildIndex;
            leftChildIndex = parentIndex*2;
        }
    }

    void fixUp(std::size_t pos) {
        while(pos > 1 && this->compare(this->data[pos/2], this->data[pos])) {
            std::swap(this->data[pos/2], this->data[pos]);
            pos /= 2;
        }
    }
}; // BinaryPQ


#endif // BINARYPQ_H
