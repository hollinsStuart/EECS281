// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
using std::deque;
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            /* TODO: After you add add one extra pointer (see below),
             *       be sure to initialize it here. */

            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, parent{ nullptr }
            {}

            // Description: Allows access to the element at that Node's
            // position.  There are two versions, getElt() and a dereference
            // operator, use whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *parent;
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
            this->root = nullptr;
            this->count = 0;
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }  {
        // TODO: Implement this function. push and loop.
        this->root = nullptr;
        this->count = 0;
        while (start != end) {
            PairingPQ::push(*start);
            ++start;
        }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        this->root = nullptr;
        this->count = 0;
        if (other.empty()) return;
        deque<Node*> list;
        Node* curr = other.root;
        list.push_back(curr);
        while(!list.empty()) {
            curr = list.front();
            list.pop_front();
            if (curr->sibling != nullptr) list.push_back(curr->sibling);
            if (curr->child != nullptr) list.push_back(curr->child);
            this->push(curr->elt);
        }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        // lecture. Use std::swap() to avoid memory leak.
        PairingPQ temp(rhs);
        std::swap(this->count, temp.count);
        std::swap(this->root, temp.root);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        if (this->root == nullptr) return;
        deque<Node*> list;
        Node* curr = this->root;
        list.push_back(curr);
        while(!list.empty()) {
            curr = list.front();
            list.pop_front();
             if (curr->sibling != nullptr) list.push_back(curr->sibling);
             if (curr->child != nullptr) list.push_back(curr->child);
            delete curr;
        }
        // if (this->root != nullptr) {
        //     deque<Node*> list;
        //     Node* curr = this->root;
        //     list.push_back(curr);
        //     while(!list.empty()) {
        //         curr = list.front();
        //         list.pop_front();
        //         if (curr->sibling != nullptr) list.push_back(curr->sibling);
        //         if (curr->child != nullptr) list.push_back(curr->child);
        //         delete curr;
        //     }
        // }
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        if (this->empty()) return;
        size_t nums = this->count;  // to restore count
        deque<Node*> list;
        Node* curr = this->root;
        list.push_back(curr);
        this->root = nullptr;
        while(!list.empty()) {
            curr = list.front();
            list.pop_front();
            if (curr->sibling != nullptr) list.push_back(curr->sibling);
            if (curr->child != nullptr) list.push_back(curr->child);
            curr->sibling = nullptr;
            curr->parent = nullptr;
            curr->child = nullptr;
            this->root = this->meld(curr, this->root);
        }
        this->count = nums;
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely
    //              in the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the pairing heap is empty. Though you are welcome to
    // if you are familiar with them, you do not need to use exceptions in
    // this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        if (this->empty()) return;
        if (this->size() == 1) {
            delete this->root;
            this->root = nullptr;
            this->count = 0;
            return;
        }     
        Node* candidate = root->child;
        deque<Node*> children;
        while(candidate!=nullptr) {
            children.push_back(candidate);
            if (candidate->sibling!=nullptr) {
                candidate = candidate->sibling;
            } else break;
        } // listing candidates
        while (children.size() > 1) {
            Node* a = children.front();
            a->sibling = nullptr;
            a->parent = nullptr;
            children.pop_front();
            Node* b = children.front();
            children.pop_front();
            b->sibling = nullptr;
            b->parent = nullptr;
            children.push_back(meld(a, b));
        }
        delete this->root;
        this->root = children.front();
        --this->count;
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        return this->root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return this->count;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return this->root == nullptr;
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value.  Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //              extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        node->elt = new_value;
        if (node == this->root) return;
        if (this->compare(node->getElt(), node->parent->getElt())) return;
        Node* leftMost = node->parent->child;
        if (node == leftMost) {
            node->parent->child = node->sibling;
        } else {
            while(leftMost->sibling!=node) {
                leftMost = leftMost->sibling;
            }
            leftMost->sibling = node->sibling;
        }
        node->parent = nullptr;
        node->sibling = nullptr;
        this->root = meld(node, this->root);
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // Runtime: O(1)
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    Node* addNode(const TYPE &val) {
        Node* newNode = new Node(val);
        this->root = this->meld(this->root, newNode);
        ++this->count;
        return newNode;
    } // addNode()


private:
    Node* root;
    size_t count{};

    // Description: input two roots of heaps, meld the heaps
    //      A, B have no parent or sibling
    //      returns the new root
    Node* meld(Node* rootA, Node* rootB) {
        if (rootA == nullptr) {
            return rootB;
        } else if (rootB == nullptr) {
            return rootA;
        } else if (rootA == rootB) return rootA;
        if (this->compare(rootA->elt, rootB->elt)) {
            // B bigger
            rootA->parent = rootB;
            if (rootB->child != nullptr) rootA->sibling = rootB->child;
            rootB->child = rootA;
            return rootB;
        } else {
            rootB->parent = rootA;
            if (rootA->child != nullptr) rootB->sibling = rootA->child;
            rootA->child = rootB;
            return rootA;
        }

    }
};


#endif // PAIRINGPQ_H
