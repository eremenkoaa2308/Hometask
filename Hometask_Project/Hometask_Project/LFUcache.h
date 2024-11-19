#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include <list>

class LFUCache {
private:
    struct Node {
        int key;    // Ключ
        int value;  // Значение
        int freq;   // Частота доступа
        Node(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity;  // Максимальная вместимость кэша
    int minFreq;   // Минимальная частота использования
    std::unordered_map<int, std::list<Node>::iterator> keyNode;  // Хранит ключи и их итераторы
    std::unordered_map<int, std::list<Node>> freqList;    // Хранит списки узлов по частоте использования

public:
    // Конструктор с заданной вместимостью
    LFUCache(int cap);

    // Получить значение по ключу
    int get(int key);

    // Добавить или обновить элемент в кэше
    void put(int key, int value);

    // Получить частоту использования и соответствующие элементы
    const std::unordered_map<int, std::list<Node>>& getfreqlist() const;
};

#endif // LFUCACHE_H
