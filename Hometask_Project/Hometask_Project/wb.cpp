#include "WriteBackCache.h"

WriteBackCache::WriteBackCache(size_t cap) : capacity(cap) {}

void WriteBackCache::writeBack(int key) {
    if (dirtyFlags[key]) {
        std::cout << "Writing back key: " << key << " with value: " << cache[key].first << "\n";
        dirtyFlags[key] = false;  
    }
}

int WriteBackCache::get(int key) {
    if (cache.find(key) == cache.end()) {
        return -1; 
    }
    
    keys.erase(cache[key].second);
    keys.push_front(key);
    cache[key].second = keys.begin();

    return cache[key].first;
}

int WriteBackCache::getValue(int key) {
    if (cache.find(key) != cache.end()) {
        return cache[key].first;
    }
    return -1;
}

void WriteBackCache::put(int key, int value) {
    if (cache.find(key) != cache.end()) {
        keys.erase(cache[key].second);
    } 
    else if (cache.size() == capacity) {
        int lru = keys.back();
        writeBack(lru);  
        keys.pop_back();
        cache.erase(lru);
        dirtyFlags.erase(lru);
    }

    keys.push_front(key);
    cache[key] = { value, keys.begin() };
    dirtyFlags[key] = false;  
}

void WriteBackCache::markDirty(int key) {
    if (cache.find(key) != cache.end()) {
        dirtyFlags[key] = true;
    }
}

void WriteBackCache::display() {
    std::cout << "Cache contains:\n";
    for (const auto& key : keys) {
        int value = getValue(key);
        std::cout << "Key: " << key << ", Value: " << value 
                  << ", Dirty: " << (dirtyFlags[key] ? "Yes" : "No") << "\n";
    }
}