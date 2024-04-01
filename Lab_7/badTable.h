//
// Created by fs200 on 2023/11/4.
//

#ifndef LAB_7_BADTABLE_H
#define LAB_7_BADTABLE_H

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

// A bucket's status tells you whether it's empty, occupied,
// or contains a deleted element.
using namespace std;

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

    HashTable() {
        buckets.resize(2);
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    V& operator[](const K& key) {
        Hasher hasher;
        size_t desired_bucket = hasher(key) % buckets.size();
        size_t i = checkBucket(desired_bucket, key);

        V v;
        if (buckets[i].status != Status::Occupied) {
            insert(key, v);
        }
        desired_bucket = hasher(key) % buckets.size();
        i = checkBucket(desired_bucket, key);
        return buckets[i].val;
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const K& key, const V& val) {

        //Check if it exists in the table
        Hasher hasher;
        size_t desired_bucket = hasher(key) % buckets.size();

        //iterate through until you find an empty spot or you find the spot
        size_t i = checkBucket(desired_bucket, key);

        //Either put it in the spot or return false since you found it
        if (buckets[i].status != Status::Occupied) {
            buckets[i] = Bucket{ Status::Occupied, key, val };
            ++num_elements;
        }
        else
            return false;

        //Grow the boy to keep good ratio
        if (double(num_elements) / double(buckets.size()) > 0.5) {
            rehash_and_grow();
        }
        return true;

    }
    // erase returns the number of items remove (0 or 1)
    size_t erase(const K& key) {
        Hasher hasher;
        size_t desired_bucket = hasher(key) % buckets.size();
        size_t i = checkBucket(desired_bucket, key);

        if (buckets[i].status == Status::Occupied) {
            buckets[i].status = Status::Deleted;
            num_elements--;
            return 1;
        }

        return 0;
    }

private:
    size_t num_elements = 0;
    size_t num_deleted = 0; // OPTIONAL: you don't need to use this to pass
    std::vector<Bucket> buckets;

    //Create new vector with double the size
    //Insert all elements that aren't of type empty in to new vector
    void rehash_and_grow() {
        vector<Bucket> bucketCopy = buckets;
        buckets.clear();
        buckets.resize(bucketCopy.size()*2);
        num_elements = 0;

        //Iterate through bucketCopy inserting all nonEmpty buckets
        for (auto i : bucketCopy) {
            if (i.status == Status::Occupied)
                insert(i.key, i.val);
        }
    }

    size_t checkBucket(size_t desiredBucket, const K& key) {
        size_t doubleCheck = desiredBucket;
        int loops = 0;
        //Run through until we either find the value or hit an empty
        while (buckets[desiredBucket].status != Status::Empty && loops < buckets.size()) {

            //If occupied check the key
            if (buckets[desiredBucket].status == Status::Occupied && buckets[desiredBucket].key == key) {
                return desiredBucket;
            }
            desiredBucket = (desiredBucket+1) % buckets.size();
            loops++;
        }
        loops = 0;
        //If we hit an empty check for deleted
        while (buckets[doubleCheck].status == Status::Occupied && loops < buckets.size()) {
            doubleCheck = (doubleCheck + 1) % buckets.size();
            loops++;
        }

        return doubleCheck;
    }

};

#endif //LAB_7_BADTABLE_H
