#include <chrono>
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
        // if (map[a[right++]]-- > 0) count--;
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
            // if (map[a[left++]]++ == 0) count++;
            char d = a[left];
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
        auto start = chrono::high_resolution_clock::now();
        string a, b;
        cin >> a >> b;
        cout << findStr(a, b) << endl;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // 计算程序运行时长
        cout << "程序运行时长：" << duration.count() / 1000.0 << "ms" << endl; // 输出程序运行时长

        return 0;
    }
    
    string a, b;
    cin >> a >> b;
    cout << findStr(a, b) << endl;

    return 0;
}