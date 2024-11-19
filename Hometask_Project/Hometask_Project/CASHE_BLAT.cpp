#include "CACHE_BLAT.h"
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <chrono>

using namespace std;

int mru(vector<int>& pages, int num_frames) {
    unordered_set<int> frames;       // ��������� ������� ������� � ������
    stack<int> recent_pages;         // ���� ��� ������������ ������� ������������� �������
    int page_faults = 0;             // ������� ��������
    int operations = 0;              // ������� ��������

    auto start_time = chrono::high_resolution_clock::now(); // ������ ������� ������ ���������

    for (int page : pages) {
        operations++; // ������� ��������� � ��������
        cout << "��������� ��������: " << page << endl;

        // ���� �������� ��� � ������, ��������� � ��� ����� ������� ��������������
        if (frames.find(page) != frames.end()) {
            stack<int> temp;
            while (!recent_pages.empty() && recent_pages.top() != page) {
                temp.push(recent_pages.top());
                recent_pages.pop();
            }
            if (!recent_pages.empty()) {
                recent_pages.pop();
            }
            while (!temp.empty()) {
                recent_pages.push(temp.top());
                temp.pop();
                operations++; // ������ �������� ����������/�������� ���������
            }
            recent_pages.push(page);
            cout << "�������� ��� � �����. ���������." << endl;
        }
        else {
            // ���� ������ (�������� ����������� � ������)
            page_faults++;
            cout << "������ ��������. ";

            // ���� ���� ����� � ������
            if (frames.size() < num_frames) {
                frames.insert(page);
                recent_pages.push(page);
                cout << "��������� � ������ ����." << endl;
            }
            else {
                // ������ ��������
                int mru_page = recent_pages.top(); // �������� ����� ������� �������������� ��������
                recent_pages.pop();
                frames.erase(mru_page);           // ������� � �� ���������
                frames.insert(page);              // ��������� ����� ��������
                recent_pages.push(page);          // ��������� � � ����
                operations += 3; // �������� �� ����� + ������� � ����� + ���������� � ����
                cout << "������ �������� " << mru_page << " �� " << page << "." << endl;
            }
        }

        // ����� �������� ��������� ������
        cout << "������� ��������� ������: ";
        for (int frame : frames) {
            cout << frame << " ";
        }
        cout << endl;
    }

    auto end_time = chrono::high_resolution_clock::now(); // ����� ������� ������ ���������
    chrono::duration<double> elapsed = end_time - start_time;

    // ����� �����������
    cout << "����� ���������� ��������: " << operations << endl;
    cout << "���������� �������� �������: " << page_faults << endl;
    cout << "����� ������ ���������: " << elapsed.count() << " ������" << endl;

    return page_faults;
}
