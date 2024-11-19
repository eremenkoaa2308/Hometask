#include "FIFOCache.h"
#include "LRUCache.h"
#include "CACHE_BLAT.h"
#include "LFUcache.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <chrono>
#include <unordered_map>
using namespace std;

void lru_test(std::list<int>& data_list, int cache_size) {
    std::cout << "TESTING LRU CACHE" << std::endl;

    LRUCache lruCache(cache_size);
    int totalOperations = 0;
    int cacheMisses = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int key : data_list) {
        int value = key * 10;
        if (lruCache.get(key) == -1) {
            cacheMisses++;
            lruCache.put(key, value);
        }

        totalOperations++;
        lruCache.display();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Total operations: " << totalOperations << std::endl;
    std::cout << "Cache misses: " << cacheMisses << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}
void fifo_test(int cache_size, std::list<int>& data_list, std::string& filename) {
    std::cout << "TESTING FIFO CACHE" << std::endl;

    FIFOCache<int> fifoCache(cache_size, filename);

    auto start = std::chrono::high_resolution_clock::now();

    fifoCache.Processing(fifoCache, data_list);

    auto end = std::chrono::high_resolution_clock::now();
    auto overall_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Cache misses: " << fifoCache.getMisses() << std::endl;
    std::cout << "Cache hits: " << fifoCache.getHits() << std::endl;
    std::cout << "Time taken: " << overall_time.count() << " microseconds" << std::endl;
}
void mru_test(std::vector<int>& data_list, int cache_size) {
    std::cout << "TESTING MRU CACHE" << std::endl;
    cout << "Количество промахов (page faults): " << mru(data_list,cache_size) << endl;
}
#include <list>
#include <chrono>
#include <iostream>
#include "WriteBackCache.h"

void wb_test(std::list<int>& data_list, int cache_size) {
    std::cout << "TESTING WRITE-BACK CACHE" << std::endl;

    WriteBackCache wbCache(cache_size); // Инициализация WriteBackCache
    int totalOperations = 0;
    int cacheMisses = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int key : data_list) {
        int value = key * 10;

        if (wbCache.get(key) == -1) {
            // Если ключ отсутствует в кэше (cache miss)
            cacheMisses++;
            wbCache.put(key, value);
        }
        else {
            // Если ключ уже в кэше, помечаем его как грязный
            wbCache.markDirty(key);
        }

        totalOperations++;
        wbCache.display(); // Отображение текущего состояния кэша
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Total operations: " << totalOperations << std::endl;
    std::cout << "Cache misses: " << cacheMisses << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}
void lfu_test(std::list<int>& data_list, int cache_size) {
    std::cout << "TESTING LFU CACHE" << std::endl;

    LFUCache lfuCache(cache_size); // Инициализация LFUCache
    int totalOperations = 0;
    int cacheMisses = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int key : data_list) {
        int value = key * 10;

        if (lfuCache.get(key) == -1) {
            // Если ключ отсутствует в кэше (cache miss)
            cacheMisses++;
            lfuCache.put(key, value);
        }

        totalOperations++;

        // Отображение текущего состояния кэша
        std::cout << "After processing key: " << key << "\n";
        std::cout << "Cache contains:\n";

        // Отображение частот и ключей
        for (auto& freq : lfuCache.getfreqlist()) {
            std::cout << "Frequency " << freq.first << ": ";
            for (auto& node : freq.second) {
                std::cout << "{Key: " << node.key << ", Value: " << node.value << "} ";
            }
            std::cout << "\n";
        }
        std::cout << "---------------------------\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Total operations: " << totalOperations << std::endl;
    std::cout << "Cache misses: " << cacheMisses << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int i;
    int cache_size = 3;
    std::list<int> data_list = { 1, 2, 3, 4, 2, 5, 1, 3 };
    lru_test(data_list,cache_size);
    std::vector<int> data_list_v = { 1, 2, 3, 4, 2, 5, 1, 3 };
    std::string filename = "data.txt";
    cout << "------------" << endl;
    fifo_test(cache_size, data_list, filename);
    cout << "------------" << endl;
    mru_test(data_list_v, cache_size);
    std::cout << "---------------------------\n";
    wb_test(data_list, cache_size);

    lfu_test(data_list, cache_size);
}
