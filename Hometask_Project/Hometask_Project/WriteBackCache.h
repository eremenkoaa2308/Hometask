#pragma once
#include <unordered_map>
#include <list>
#include <iostream>

class WriteBackCache
{
private:
    size_t capacity;
    std::list<int> keys;
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> cache;
    std::unordered_map<int, bool> dirtyFlags;  

    void writeBack(int key); 

public:
    explicit WriteBackCache(size_t cap);
    
    int get(int key);
    
    int getValue(int key);

    void put(int key, int value);

    void markDirty(int key);  

    void display();
};