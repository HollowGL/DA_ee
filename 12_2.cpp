#include <cstdio>
#include <algorithm>
typedef unsigned short ushort;

bool debug = false;

struct Food {
    ushort index;
    ushort nutrients;
};

ushort binFromList(ushort len) {
    ushort res = 0, temp;
    for (int i = 0; i < len; ++i) {
        scanf("%hu", &temp);
        res |= 1 << (temp - 1);
    }
    return res;
}

int count1 (ushort num) {
    int res = 0;
    while (num) {
        res += num & 1;
        num >>= 1;
    }
    return res;
}

bool cmp(Food a, Food b) {
    return count1(a.nutrients) > count1(b.nutrients);
}

bool satisfy(ushort s, ushort t) {
    return (s | t) == s;
}

ushort N, M, target = 0;
ushort Mi[65540], Ni[16], resList[16];
Food dp[65540];

int main() {
    if (debug) freopen("./data.in", "r", stdin);

    scanf("%hu%hu", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%hu", &Mi[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%hu", &Ni[i]);
        target |= 1 << (Ni[i] - 1);
    }
    for (int i = 0; i < M; ++i) {
        dp[i].index = i;
        dp[i].nutrients = binFromList(Mi[i]);
    }

    if (debug) {
        for (int i = 0; i < M; ++i) {
            printf("第%d种食物含有营养%hx\n", i, dp[i].nutrients);
        }
        printf("营养需求为: ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", Ni[i]);
        }
        printf("\n");
    }

    std::sort(dp, dp + M, cmp); // 按含营养数量从大到小排序

    if (debug) {
        printf("排序后:\n");
        for (int i = 0; i < M; ++i) {
            printf("第%d种食物含有营养%hx，索引为%d\n", i, dp[i].nutrients, dp[i].index);
        }
    }

    // 从营养最多的食物开始选，直到满足所有营养需求
    int cur = 0;
    int p = 0;
    for (int i = 0; i < M; ++i) {
        if (satisfy(cur, target)) break;
        if ((cur | dp[i].nutrients) == cur) continue; // 营养重复
        cur |= dp[i].nutrients;
        resList[p] = i;
        p++;
        if (debug) {
            printf("第%d种食物加入，营养为%hu，索引为%d\n", i, dp[i].nutrients, dp[i].index);
        }
    }
    
    if (!satisfy(cur, target)) {
        printf("-1\n");
        return 0;
    }

    if (debug) {
        printf("\n");
        printf("删除前: p = %d\n", p);
        for (int i = 0; i < p; ++i) {
            printf("%d ", dp[resList[i]].index);
        }
        printf("\n");
        printf("删除后:\n");
    }

    // 从营养最少的食物开始删除
    bool exist[16] = {false};
    for (int i = 0; i < p; ++i) {
        exist[resList[i]] = true;
    }
    
    int q = p - 1;
    while (q >= 0) {
        exist[resList[q]] = false;
        int cur2 = 0;
        for (int i = 0; i < p; ++i) {
            if (exist[resList[i]]) {
                cur2 |= dp[resList[i]].nutrients;
            }
        }
        if (!satisfy(cur2, target)) {
            exist[resList[q]] = true;
        }
        q--;
    }

    for (int i = 0; i < p; ++i) {
        if (exist[resList[i]]) {
            printf("%d ", dp[resList[i]].index);
        }
    }



    return 0;
}
