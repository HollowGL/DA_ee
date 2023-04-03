#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std;

bool debug = true;


string findStr(string& a, string& b) {
    unordered_map<char, int> charB;
    for (int i = 0; i < b.size(); i++) {
        charB[b[i]]++;
    }

    int left = 0, right = 0, resLeft = -1, resRight = -1;
    int resLen = a.size() + 1;
    int charBLen = charB.size();
    unordered_map<char, int> window;
    int windowLen = 0;

    while (right < a.size()) {
        char c = a[right];
        window[c]++;
        right++;
        // 调用一次charB[c]，如果c不存在，就会默认添加一个键值对导致charB.size()+1，所以得用count()
        if (charB.count(c) && window[c] == charB[c]) {  
            windowLen++;                                    
        }
        while (windowLen == charBLen && left <= right) {
            if ((right - left) < resLen) {
                resLeft = left;
                resRight = right;
                resLen = right - left;
            }
            char d = a[left];
            window[d]--;
            left++;
            if (charB.count(d) && window[d] < charB[d]) {
                windowLen--;
            }
        }
    }
    if (resLeft == -1 || resRight == -1) {
        return "-1";
    }
    return a.substr(resLeft, resLen);
}

int main() {
    if (debug) {
        freopen("data.in", "r", stdin);
    }
    
    auto start = chrono::high_resolution_clock::now();
    string a, b;
    cin >> a >> b;
    cout << findStr(a, b) << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // 计算程序运行时长
    cout << "程序运行时长：" << duration.count() / 1000.0 << "ms" << endl; // 输出程序运行时长
    return 0;
}
