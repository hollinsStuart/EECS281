// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B
// tar -czvf lab7.tar.gz hashtable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Key&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

// SUBMISSION INSTRUCTIONS:
// Submit this file, by itself, in a .tar.gz.
// Other files will be ignored.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!
#include <iostream>

using std::cout, std::endl;

// A bucket's status tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class Status : uint8_t {
    Empty,
    Occupied,
    Deleted
};

template<typename K, typename V, typename Hasher = std::hash<K>>
class HashTable {
    // used by the autograder; do not change/remove.
    friend class Verifier;
public:
    // A bucket has a status, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        Status status = Status::Empty;
        K key;
        V val;
    };

    HashTable() : num_elements{0} {
        this->buckets = std::vector<Bucket> (5, Bucket());
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    V& operator[](const K& key) {
        if (this->buckets.size() < this->num_elements*2) this->rehash_and_grow();
        int find = search(key);
        if (find == -1) {
            // not in the table, insert and return
            int pos = newKey(key);
            this->buckets[pos].val = V();
            this->buckets[pos].key = key;
            this->buckets[pos].status = Status::Occupied;
            ++this->num_elements;
            return buckets[pos].val;
        } else {
            // in the table
            return buckets[find].val;
        }
        // should not run the following
        std::cerr << "operator[] fell through" << endl;
        return this->buckets[0].val;
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const K& key, const V& val) {
        if (this->buckets.size() < this->num_elements*2) this->rehash_and_grow();
        int index = search(key);
        if (index != -1) return false;
        int pos = newKey(key);
        this->buckets[pos].val = val;
        this->buckets[pos].key = key;
        this->buckets[pos].status = Status::Occupied;
        ++this->num_elements;
        return true;
    }

    // erase returns the number of items remove (0 or 1)
    size_t erase(const K& key) {
        int pos = search(key);
        if (pos == -1) return 0;
        this->buckets[pos].status = Status::Deleted;
        --this->num_elements;
        return 1;
    }

    int getSearch(const K& key) const {
        return search(key);
    }

    void printAll() {
        std::cout << "#Elements: " << this->num_elements << endl;
        std::cout << "#Bucket size: " << this->buckets.size() << endl;
        for (int i = 0; i < (int)this->buckets.size(); ++i) {
            cout << "\tvalue: " << buckets[i].val << "\tkey: " << buckets[i].key << "\t";
            if (buckets[i].status == Status::Empty) cout << "\tEmpty" << endl;
            if (buckets[i].status == Status::Occupied) cout << "Occupied" << endl;
            if (buckets[i].status == Status::Deleted) cout << "Deleted" << endl;
        }
    }

private:
    size_t num_elements = 0;
    std::vector<Bucket> buckets;

    // You can avoid implementing rehash_and_grow() by calling
    //    buckets.resize(10000);
    // in the constructor. However, you will only pass the AG test cases ending in _C.
    // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
    void rehash_and_grow() {
        size_t new_size = 2 * this->buckets.size();
        std::vector<Bucket> oldBuckets = this->buckets;
        this->buckets = std::vector<Bucket>(new_size, Bucket());
        this->num_elements = 0;
        for (int i = 0; i < (int)oldBuckets.size(); ++i) {
            if (oldBuckets[i].status == Status::Occupied) {
                this->insert(oldBuckets[i].key, oldBuckets[i].val);
            }
        }
    }

    // You can add methods here if you like.

    /* return the index in the vector, -1 if not found */
    int search(const K& key) const {
        if (this->num_elements == 0) return -1;
        Hasher hasher;
        int index = hasher(key) % (int)this->buckets.size();
        for (int i = 0; i < (int)this->buckets.size(); ++i) {
            if (this->buckets[index].status == Status::Occupied) {
                if (this->buckets[index].key == key) return index;
            } else if (this->buckets[index].status == Status::Empty) {
                return -1;
            }
            index = (index+1) % (int)this->buckets.size();
        }
        return -1;
    }

    /* return the index that the new key should be at */
    int newKey(const K& key) {
//        if (search(key)!=-1) std::cerr << "bad new key: " << key << endl;
        Hasher h;
        if (this->buckets.size() < this->num_elements*2) this->rehash_and_grow();
        int index = h(key) % (int)this->buckets.size();;
        for (int i = 0; i < (int)buckets.size(); ++i) {
            if (buckets[index].status != Status::Occupied) {
                return index;
            }
            index = (index+1) % (int)buckets.size();
        }
        std::cerr << "newKey fell through" << endl;
        return -1;
    }

    void printBucket(Bucket b) {
        cout << "\tvalue: " << b.val << "\tkey: " << b.key << "\t";
        if (b.status == Status::Empty) cout << "\tEmpty" << endl;
        if (b.status == Status::Occupied) cout << "Occupied" << endl;
        if (b.status == Status::Deleted) cout << "Deleted" << endl;
    }
};

#endif // HASHTABLE_H