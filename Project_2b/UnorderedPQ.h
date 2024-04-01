// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E


#ifndef UNORDEREDPQ_H
#define UNORDEREDPQ_H

#include "Eecs281PQ.h"


// A specialized version of the priority queue ADT that is implemented with
// an underlying unordered array-based container that is linearly searched
// for the most extreme element every time it is needed.

// TODO: Read and understand this priority queue implementation!
// Pay particular attention to how the constructors and findExtreme()
// are written, especially the use of this->compare.

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class UnorderedPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with optional comparison functor.
    // Runtime: O(1)
    explicit UnorderedPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
    } // UnorderedPQ()


    // Description: Construct a PQ out of an iterator range with optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    UnorderedPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, data{ start, end } {
    } // UnorderedPQ()


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~UnorderedPQ() {
    } // ~UnorderedPQ()


    // Description: Does nothing for this implementation, as items can never
    //              be 'out of order'.
    // Runtime: O(1)
    virtual void updatePriorities() {
    } // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: Amortized O(1)
    virtual void push(const TYPE &val) {
        data.push_back(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(n)
    // Note: If the most extreme element is already known (as would happen if
    //       .top() was called before .pop()), this function is O(1).
    virtual void pop() {
        // Replace the most extreme element with the element at the back,
        // then pop_back().  This is much faster than erasing from the middle
        // of a vector.
        data[findExtreme()] = data.back();
        data.pop_back();
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the vector.  This should be a reference for speed.  It
    //              MUST be const because we cannot allow it to be modified,
    //              as that might make it no longer be the most extreme
    //              element.
    // Runtime: O(n)
    virtual const TYPE &top() const {
        // Find the most extreme element and return it by const reference.
        return data[findExtreme()];
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return data.size();
    } // size()

    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return data.empty();
    } // empty()


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;

private:
    // Description: Find the 'most extreme' element of the data vector, using
    //              this->compare() to check if one element is 'less than'
    //              another.
    // Runtime: O(n)
    size_t findExtreme() const {
        size_t index = 0;

        for (size_t i = 1; i < data.size(); ++i)
            if (this->compare(data[index], data[i]))
                index = i;

        return index;
    } // findExtreme()
}; // UnorderedPQ

#endif // UNORDEREDPQ_H
