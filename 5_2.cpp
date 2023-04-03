#include <chrono>
#include <iostream>
#include <unordered_map>
using namespace std;

bool debug = true;

string findStr(const string &a, const string &b) {
    unordered_map<char, int> charB;
    for (char c : b) {
        charB[c]++;
    }

    int l = 0, r = 0, start = -1;
    int rseLen = a.size() + 1; 
    int count = charB.size();

    while (r < a.size()) {
        char c = a[r];
        if (charB.count(c)) {
            charB[c]--;
            if (charB[c] == 0) {
                count--;
            }
        }
        r++;

        while (count == 0 && l <= r) {
            if (r - l < rseLen) {
                rseLen = r - l;
                start = l;
            }

            char d = a[l];
            if (charB.count(d)) {
                charB[d]++;
                if (charB[d] > 0) {
                    count++;
                }
            }
            l++;
        }
    }

    if (start == -1) {
        return "-1";
    } else {
        return a.substr(start, rseLen);
    }
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