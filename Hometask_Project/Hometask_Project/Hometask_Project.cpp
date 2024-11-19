
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
        lruCache.put(j, j * 10); // Например, ключ = j, значение = j * 10
        totalOperations++;
    }

    lruCache.display();

    // Запрашиваем несколько элементов, включая один, который не существует
    for (int j = 1; j <= i; j++) {
        if (lruCache.get(j) == -1) cacheMisses++;
        totalOperations++;
    }

    // Запрашиваем элемент, который не существует
    if (lruCache.get(i + 1) == -1) cacheMisses++;
    totalOperations++; // Пропуск

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

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Total operations: " << totalOperations << std::endl;
    std::cout << "Cache misses: " << cacheMisses << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}

int main()
{
    int i;
    cout << "Enter size of lru_cache mas" << endl;
    cin >> i;
    lru_test(i);
}
