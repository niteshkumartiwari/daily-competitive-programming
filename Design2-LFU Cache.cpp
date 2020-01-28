/*
Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Note that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

 

Follow up:
Could you do both operations in O(1) time complexity?

 

Example:

LFUCache cache = new LFUCache( 2 //capacity  );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class LFUCache {
    int capacity, minFreq;
    unordered_map<int, pair<int, int>> keyValFreq;
    unordered_map<int, list<int>> freqKey;
    unordered_map<int, list<int>::iterator> keyIter;

   public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (keyValFreq.find(key) == keyValFreq.end())
            return -1;
        int freq = keyValFreq[key].second;
        freqKey[freq++].erase(keyIter[key]);
        freqKey[freq].emplace_front(key);
        keyIter[key] = freqKey[freq].begin();
        keyValFreq[key].second = freq;

        if (freqKey[minFreq].empty()) minFreq = freq;

        return keyValFreq[key].first;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        if (get(key) != -1) {
            keyValFreq[key].first = value;
            return;
        }

        if (keyValFreq.size() == capacity) {
            int delKey = freqKey[minFreq].back();
            freqKey[minFreq].pop_back();
            keyValFreq.erase(delKey);
            keyIter.erase(delKey);
        }

        minFreq = 1;
        keyValFreq[key] = make_pair(value, minFreq);
        freqKey[minFreq].emplace_front(key);
        keyIter[key] = freqKey[minFreq].begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    return 0;
}
