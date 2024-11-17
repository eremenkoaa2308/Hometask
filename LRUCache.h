#include <unordered_map>
#include <list>
#include <iostream>
#pragma once

using namespace std;

class LRUCache
{
private:
    size_t capacity;
    list<int> keys;
    unordered_map<int, pair<int, list<int>::iterator>> cache;

public:
    explicit LRUCache(size_t cap);

    int get(int key);

    int getValue(int key);

    void put(int key, int value);

    void display();
};

