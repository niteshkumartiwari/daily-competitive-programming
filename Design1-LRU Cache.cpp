/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 //capacity );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

#include<bits/stdc++.h>
using namespace std;

class LRUCache {
    list<int> mylist;//key list
    unordered_map<int, pair<int,list<int>::iterator>> um;//um[key]={value,*itr}
    int size;  
public:
    LRUCache(int capacity) {
        size=capacity;
    }
    
    int get(int key) {
        if(um.count(key)==0) return -1;

        mylist.erase(um[key].second);
        mylist.push_front(key);
        um[key].second= mylist.begin();
       
       return um[key].first;
    }
    
    void put(int key, int value) {
        if(um.count(key)!=0){//key already exists
            mylist.erase(um[key].second);
            mylist.push_front(key);
            um[key].first=value;
            return ;
        }

        if(mylist.size()==size){
            um.erase(mylist.back());
            mylist.pop_back();
        }
        
        mylist.push_front(key);
        um[key]={value,mylist.begin()};
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(){
    LRUCache *lru= new LRUCache(2);
    cout<<lru->get(2)<<endl;
    lru->put(2,6);
    cout<<lru->get(1)<<endl;
    lru->put(1,5);
    lru->put(1,2);
    cout<<lru->get(1)<<endl;
    cout<<lru->get(2)<<endl;


    return 0;
}