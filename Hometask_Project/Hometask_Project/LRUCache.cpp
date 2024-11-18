#include "LRUCache.h"

LRUCache::LRUCache(size_t cap) : capacity(cap) {}

int LRUCache::get(int key) {
    if (cache.find(key) == cache.end()) {
        return -1;
    }

    keys.erase(cache[key].second);
    keys.push_front(key);
    cache[key].second = keys.begin();

    return cache[key].first;
}

int LRUCache::getValue(int key) {
    if (cache.find(key) != cache.end()) {
        return cache[key].first;
    }
    return -1;
}

void LRUCache::put(int key, int value) {
    if (cache.find(key) != cache.end()) {
        keys.erase(cache[key].second);
    }
    else if (cache.size() == capacity) {
        int lru = keys.back();
        keys.pop_back();
        cache.erase(lru);
    }

    keys.push_front(key);
    cache[key] = { value, keys.begin() };
}

void LRUCache::display() {
    std::cout << "Cache contains:\n";
    for (const auto& key : keys) {
        int value = getValue(key);
        std::cout << "Key: " << key << ", Value: " << value << "\n";
    }
}