#include "BLATOV.h"
#include <unordered_set>
#include <stack>

using namespace std;

int mru(vector<int> pages, int num_frames) {
    unordered_set<int> frames;
    stack<int> recent_pages;
    int page_faults = 0;

    for (int page : pages) {
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
            }
            recent_pages.push(page);
            continue;
        }

        page_faults++;

        if (frames.size() < num_frames) {
            frames.insert(page);
            recent_pages.push(page);
        }
        else {
            int mru_page = recent_pages.top();
            recent_pages.pop();
            frames.erase(mru_page);
            frames.insert(page);
            recent_pages.push(page);
        }
    }

    return page_faults;
}
