/*
滑动窗口求最小包含子串：https://leetcode.cn/problems/minimum-window-substring/description/
*/

#include <iostream>
using namespace std;

bool debug = true;


string findStr(const string& a, const string& b) {
    int map[256] = { 0 };
    for (auto i : b) {
        map[i]++;
    }
    int left = 0, right = 0, count = b.size(), resLength = INT_MAX, start = 0;
    while (right < a.size()) {
        char c = a[right];
        if (map[c] > 0) {
            count--;
        }
        map[c]--;
        right++;
        while (count == 0) {
            if (right - left < resLength) {
                resLength = right - left;
                start = left;
            }
            char d = a[left];
            // right指针在前，已将所有b中字符在map中减去，
            // 此时map中b的字符均为0，其它的则为负数，
            // 当left指针指向一个0值，意味着遇到b中字符，不可再缩减
            if (map[d] == 0) {
                count++;
            }
            map[d]++;
            left++;
        }
    }
    if (resLength == INT_MAX) return "-1";
    return a.substr(start, resLength);
}


int main() {

    if (debug) {
        freopen("data.in", "r", stdin);
    }
    
    string a, b;
    cin >> a >> b;
    cout << findStr(a, b) << endl;

    return 0;
}