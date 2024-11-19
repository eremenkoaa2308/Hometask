#include "CACHE_BLAT.h"
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <chrono>

using namespace std;

int mru(vector<int>& pages, int num_frames) {
    unordered_set<int> frames;       // Множество текущих страниц в кадрах
    stack<int> recent_pages;         // Стек для отслеживания порядка использования страниц
    int page_faults = 0;             // Счётчик промахов
    int operations = 0;              // Счётчик операций

    auto start_time = chrono::high_resolution_clock::now(); // Начало времени работы алгоритма

    for (int page : pages) {
        operations++; // Считаем обращение к странице
        cout << "Обработка страницы: " << page << endl;

        // Если страница уже в кадрах, обновляем её как самую недавно использованную
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
                operations++; // Каждое действие добавления/удаления считается
            }
            recent_pages.push(page);
            cout << "Страница уже в кадре. Обновлено." << endl;
        }
        else {
            // Если промах (страница отсутствует в кадрах)
            page_faults++;
            cout << "Промах страницы. ";

            // Если есть место в кадрах
            if (frames.size() < num_frames) {
                frames.insert(page);
                recent_pages.push(page);
                cout << "Добавлено в пустой кадр." << endl;
            }
            else {
                // Замена страницы
                int mru_page = recent_pages.top(); // Получаем самую недавно использованную страницу
                recent_pages.pop();
                frames.erase(mru_page);           // Удаляем её из множества
                frames.insert(page);              // Добавляем новую страницу
                recent_pages.push(page);          // Добавляем её в стек
                operations += 3; // Удаление из стека + вставка в кадры + добавление в стек
                cout << "Замена страницы " << mru_page << " на " << page << "." << endl;
            }
        }

        // Вывод текущего состояния кадров
        cout << "Текущее состояние кадров: ";
        for (int frame : frames) {
            cout << frame << " ";
        }
        cout << endl;
    }

    auto end_time = chrono::high_resolution_clock::now(); // Конец времени работы алгоритма
    chrono::duration<double> elapsed = end_time - start_time;

    // Вывод результатов
    cout << "Общее количество операций: " << operations << endl;
    cout << "Количество промахов страниц: " << page_faults << endl;
    cout << "Время работы алгоритма: " << elapsed.count() << " секунд" << endl;

    return page_faults;
}
