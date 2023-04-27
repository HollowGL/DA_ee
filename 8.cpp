#include <cstdio>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

bool debug = false;

// bool isSimilar(char s1[], char s2[]) {
//     int i = 0;
//     return false;
// }

int hashCode(string s) {
    int hash = 0, i = 0;
    for (; i < s.length(); ++i) {
        if (s[i] != '_')
            hash += s[i] - 'a';
    }
    if (s[i - 1] >= '0' && s[i - 1] <= '9') {
        hash -= s[i - 1] - 'a';
    }
    return hash;
}


int main() {

    if (debug) {
        freopen("./data.in", "r", stdin);
    }

    int foldersCnt;
    int filesCnt;
    unordered_map<string, int> strHash;

    scanf("%d", &foldersCnt);
    for (int i = 0; i < foldersCnt; i++) {
        scanf("%d", &filesCnt);
        for (int j = 0; j < filesCnt; j++) {
            string s;
            cin >> s;
            strHash[s] = hashCode(s);
            cout << s << "  ";
        }
        cout << endl;
    }

    short charCnt[2600] = {0};
    for (auto iter = strHash.begin(); iter != strHash.end(); ++iter) {
        charCnt[iter->second]++;
    }

    if (debug) {
        printf("size: \n", strHash.size());
        for (auto iter = strHash.begin(); iter != strHash.end(); ++iter) {
            cout << iter->first << "-" << iter->second << "  ";
        }
    }
    
    int max = 0;
    for (int i = 0; i < 2600; i++) {
        if (charCnt[i] > max) max = charCnt[i];
    }
    cout << max << endl;

    return 0;
}