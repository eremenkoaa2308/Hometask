#include <iostream>
#include <unordered_map>
#include <map>
#include <list>

class LFUCache {
private:
    struct Node {
        int key;
        int value;
        int freq;
        Node(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity;  // Максимальная вместимость кэша
    int minFreq;   // Минимальная частота использования
    std::unordered_map<int, std::list<Node>::iterator> keyNode; // Хранит ключи и их итераторы
    std::unordered_map<int, std::list<Node>> freqList; // Хранит списки узлов по частоте использования

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (keyNode.find(key) == keyNode.end()) {
            return -1; // Если ключ не найден
        }

        // Обновление частоты использования
        auto node = keyNode[key];
        int val = node->value, freq = node->freq;
        freqList[freq].erase(node); // Удаление узла из текущей частоты

        if (freqList[freq].empty()) {
            freqList.erase(freq);
            if (minFreq == freq) {
                ++minFreq; // Обновляем минимальную частоту
            }
        }

        // Добавление узла с новой частотой
        ++freq;
        freqList[freq].push_front({ key, val, freq });
        keyNode[key] = freqList[freq].begin();

        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyNode.find(key) != keyNode.end()) {
            // Если ключ уже существует, обновляем его значение
            auto node = keyNode[key];
            node->value = value;
            get(key); // Увеличиваем частоту
            return;
        }

        if (keyNode.size() == capacity) {
            // Удаляем наименее используемый элемент
            auto node = freqList[minFreq].back();
            keyNode.erase(node.key);
            freqList[minFreq].pop_back();

            if (freqList[minFreq].empty()) {
                freqList.erase(minFreq);
            }
        }

        // Добавление нового элемента
        minFreq = 1;
        freqList[1].push_front({ key, value, 1 });
        keyNode[key] = freqList[1].begin();
    }
};

int main() {
    LFUCache cache(3); // Инициализация кэша вместимостью 3

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    std::cout << cache.get(1) << "\n"; // Выводит 10
    cache.put(4, 40); // Удаляет ключ 2 (минимальная частота)
    std::cout << cache.get(2) << "\n"; // Выводит -1 (ключ удален)
    std::cout << cache.get(3) << "\n"; // Выводит 30
    std::cout << cache.get(4) << "\n"; // Выводит 40




    return 0;
}