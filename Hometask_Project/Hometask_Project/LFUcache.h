#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include <list>

class LFUCache {
private:
    struct Node {
        int key;    // ����
        int value;  // ��������
        int freq;   // ������� �������
        Node(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity;  // ������������ ����������� ����
    int minFreq;   // ����������� ������� �������������
    std::unordered_map<int, std::list<Node>::iterator> keyNode;  // ������ ����� � �� ���������
    std::unordered_map<int, std::list<Node>> freqList;    // ������ ������ ����� �� ������� �������������

public:
    // ����������� � �������� ������������
    LFUCache(int cap);

    // �������� �������� �� �����
    int get(int key);

    // �������� ��� �������� ������� � ����
    void put(int key, int value);

    // �������� ������� ������������� � ��������������� ��������
    const std::unordered_map<int, std::list<Node>>& getfreqlist() const;
};

#endif // LFUCACHE_H
