/*
并查集
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

bool debug = true;


// 检测是否为同一文件，有很多冗余，还可能有bug
bool isSameFile(string s1, string s2) {
    int len1 = s1.length(), len2 = s2.length();
    int lenDiff = len1 - len2;
    if (lenDiff > 1 || lenDiff < -1) {
        return false;
    }
    // 有数字
    if (s1[len1 - 1] >= '0' && s1[len1 - 1] <= '9') {
        if (s2[len2 - 1] >= '0' && s2[len2 - 1] <= '9') {
            if (s1.substr(0, len1 - 1) == s2.substr(0, len2 - 1))  // 有两个数字相同而相差下划线的清况，不能直接return
                return true;
        } else {
            return s1.substr(0, len1 - 1) == s2;
        }
    } else if (s2[len2 - 1] >= '0' && s2[len2 - 1] <= '9') {
        return s2.substr(0, len2 - 1) == s1;
    }

    // 没有（或都有）数字的话，那长度肯定不等
    if (lenDiff == 0) {
        return false;
    }

    // 下划线
    int p = 0;
    while (p < len1 && p < len2) {
        if (s1[p] != s2[p]) {
            if (s1[p] == '_') 
                return s1.replace(p, 1, "") == s2;
            return s2.replace(p, 1, "") == s1;
        }
        p++;
    }
    // 下划线出现在末尾
    if (len1 > len2) 
        return s1[p] == '_';
    else if (len1 < len2)
        return s2[p] == '_';
    return false;
}

// 删去所有下划线和数字作为键
string getKeyStr(string str) {
    int i = 0;
    for (; i < str.length(); ++i) {
        if (str[i] == '_') {
            str.replace(i, 1, "");
            i--;
        }
    }
    if (str[i - 1] >= '0' && str[i - 1] <= '9') {
        return str.substr(0, i - 1);
    }
    return str;
}

// 并查集，随着调用次数增加，复杂度趋于常数
class UnionFind {
public:
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // 不仅返回其根结点，还将沿途中的结点都指向更高一级，压缩了路径
    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    // 将深度较小的树根结点连接到深度较大的树
    void unite(int i, int j) {
        int pi = find(i), pj = find(j);
        if (pi != pj) {
            if (size[pi] < size[pj]) {
                swap(pi, pj);
            }
            parent[pj] = pi;
            size[pi] += size[pj];
        }
    }

    bool isConnected(int i, int j) {
        return (find(i) == find(j));
    }

private:
    vector<int> parent;
    vector<int> size;
};

int main() {

    if (debug) {
        freopen("./data.in", "r", stdin);
    }

    int n;
    cin >> n;

    // 将相似的文件放在一个同一个键值对下
    unordered_map<string, vector<pair<int, string>>> hashmap;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            string filename;
            cin >> filename;
            string key = getKeyStr(filename);
            hashmap[key].emplace_back(i, filename);
        }
    }

    int maxDuplicate = 0;
    for (auto iter = hashmap.begin(); iter != hashmap.end(); ++iter) {
        UnionFind uf(n);
        int duplicate = 1;
        auto key = iter->first;
        auto vals = iter->second;
        for (int i = 0; i < vals.size() - 1; ++i) {
            for (int j = 0; j < vals.size(); ++j) {
                if (uf.isConnected(vals[i].first, vals[j].first)) {
                    continue;
                }
                if (isSameFile(vals[i].second, vals[j].second)) {
                    uf.unite(vals[i].first, vals[j].first);
                    duplicate++;
                }
            }
        }
        if (duplicate > maxDuplicate)
            maxDuplicate = duplicate;
    }

    cout << maxDuplicate << endl;

    return 0;
}