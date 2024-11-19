#include "FIFOCache.h"
#include "LRUCache.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <chrono>
#include <unordered_map>
using namespace std;

void lru_test(int i) {
    cout << "TESTING LRU CACHE" << endl;
    LRUCache lruCache(i); // Создаем кэш с размером i
    int totalOperations = 0;
    int cacheMisses = 0;

    auto start = std::chrono::high_resolution_clock::now();

    // Добавляем i элементов в кэш
    for (int j = 1; j <= i; j++) {
        lruCache.put(j, j * 10);
        totalOperations++;
    }

    lruCache.display();

    // Запрашиваем несколько элементов
    for (int j = 1; j <= i; j++) {
        if (lruCache.get(j) == -1) cacheMisses++;
        totalOperations++;
    }

    // Запрашиваем элемент, который не существует
    if (lruCache.get(i + 1) == -1) cacheMisses++;
    totalOperations++;

    // Изменяем порядок использования
    lruCache.get(1); // Запрашиваем первый элемент
    totalOperations++;

    lruCache.display();
    // Добавляем новый элемент, который вызовет вытеснение
    lruCache.put(i + 1, (i + 1) * 10);
    totalOperations++;

    lruCache.display();

    // Запрашиваем элементы после добавления нового
    for (int j = 1; j <= i; j++) {
        if (lruCache.get(j) == -1) cacheMisses++;
        totalOperations++;
    }

    // Проверяем несколько пропусков
    if (lruCache.get(i + 1) == -1) cacheMisses++;
    totalOperations++;

    lruCache.display();
    // Запрашиваем все элементы, чтобы проверить, что они доступны
    for (int j = 1; j <= i; j++) {
        if (lruCache.get(j) == -1) cacheMisses++;
        totalOperations++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Total operations: " << totalOperations << std::endl;
    std::cout << "Cache misses: " << cacheMisses << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}

void fifo_test(int cache_size, const std::list<int>& data_list, const std::string& filename) {
    std::cout << "TESTING FIFO CACHE" << std::endl;

    // Create a FIFO cache with the specified cache size and filename
    FIFOCache<int> fifoCache(cache_size, filename);

    auto start = std::chrono::high_resolution_clock::now();

    fifoCache.Processing(fifoCache, data_list);

    // Display the cache hit/miss statistics and overall operations
    auto end = std::chrono::high_resolution_clock::now();
    auto overall_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    //std::cout << "Total operations: " << totalOperations << std::endl;
    std::cout << "Cache misses: " << fifoCache.getMisses() << std::endl;
    std::cout << "Cache hits: " << fifoCache.getHits() << std::endl;
    std::cout << "Time taken: " << overall_time.count() << " microseconds" << std::endl;
}

int main()
{
    int i;
    cout << "Enter size of lru_cache mas" << endl;
    cin >> i;
    //lru_test(i);
    int cache_size = 3;
    std::list<int> data_list = { 1, 2, 3, 4, 2, 5, 1, 3 };  // Example data access sequence
    std::string filename = "data.txt";  // Dummy filename for simulation

    fifo_test(cache_size, data_list, filename);

}
