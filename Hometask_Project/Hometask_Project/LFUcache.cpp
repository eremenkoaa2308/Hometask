#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include "LFUCache.h"

LFUCache::LFUCache(int cap) : capacity(cap), minFreq(0) {}

int LFUCache::get(int key) {
    if (keyNode.find(key) == keyNode.end()) {
        return -1; // ���� ���� �� ������
    }

    // ���������� ������� �������������
    auto node = keyNode[key];
    int val = node->value, freq = node->freq;
    freqList[freq].erase(node); // �������� ���� �� ������� �������

    if (freqList[freq].empty()) {
        freqList.erase(freq);
        if (minFreq == freq) {
            ++minFreq; // ��������� ����������� �������
        }
    }

    // ���������� ���� � ����� ��������
    ++freq;
    freqList[freq].push_front({ key, val, freq });
    keyNode[key] = freqList[freq].begin();

    return val;
}

void LFUCache::put(int key, int value) {
    if (capacity == 0) return;

    if (keyNode.find(key) != keyNode.end()) {
        // ���� ���� ��� ����������, ��������� ��� ��������
        auto node = keyNode[key];
        node->value = value;
        get(key); // ����������� �������
        return;
    }

    if (keyNode.size() == capacity) {
        // ������� �������� ������������ �������
        auto node = freqList[minFreq].back();
        keyNode.erase(node.key);
        freqList[minFreq].pop_back();

        if (freqList[minFreq].empty()) {
            freqList.erase(minFreq);
        }
    }

    // ���������� ������ ��������
    minFreq = 1;
    freqList[1].push_front({ key, value, 1 });
    keyNode[key] = freqList[1].begin();
}

const std::unordered_map<int, std::list<LFUCache::Node>>& LFUCache::getfreqlist() const {
    return freqList;
}
