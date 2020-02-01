/*
Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
There are two data member in the solution

a vector nums
an unordered_map m
The key of m is the val, the value of m is a vector contains indices where the val appears in nums.
Each element of nums is a pair, the first element of the pair is val itself, the second element of the pair is an index into m[val].
There is a relationship between nums and m:

m[nums[i].first][nums[i].second] == i;
*/

class RandomizedCollection {
    vector<pair<int, int>> valMapIdx;
    unordered_map<int, vector<int>> val2IdxInVec;

   public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        valMapIdx.clear();
        val2IdxInVec.clear();
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        auto res = val2IdxInVec.count(val);

        val2IdxInVec[val].push_back(valMapIdx.size());
        valMapIdx.push_back({val, val2IdxInVec[val].size() - 1});

        return res;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (val2IdxInVec.count(val) == 0) return false;

        auto last = valMapIdx.back();
        val2IdxInVec[last.first][last.second] = val2IdxInVec[val].back();
        valMapIdx[val2IdxInVec[val].back()] = last;

        valMapIdx.pop_back();
        val2IdxInVec[val].pop_back();
        if (val2IdxInVec[val].size() == 0) val2IdxInVec.erase(val);

        return true;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        return valMapIdx[rand() % valMapIdx.size()].first;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main() {
    return 0;
}
