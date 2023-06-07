#include <cstdio>
#include <algorithm>

bool debug = true;
typedef unsigned short ushort;

ushort N, M;
ushort *Mi, *Ni;
ushort dp[65540];
int res[16];

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

int main() {
    if (debug) freopen("./data.in", "r", stdin);

    scanf("%hu %hu", &N, &M);
    Mi = new ushort[M];
    for (int i = 0; i < M; ++i) {
        scanf("%hu", &Mi[i]);
    }
    Ni = new ushort[N];
    for (int i = 0; i < N; ++i) {
        scanf("%hu", &Ni[i]);
    }
    for (int i = 0; i < M; ++i) {
        dp[i] = binFromList(Mi[i]);
    }

    if (debug) {
        for (int i = 0; i < M; ++i) {
            printf("第%d种食物含有营养%hx\n", i, dp[i]);
        }
        printf("营养需求为: ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", Ni[i]);
        }
        printf("\n");
    }

    for (int j = 0; j < N; ++j) {
        res[j] = -1;
        int target = 1 << (Ni[j] - 1); // 所需营养j的二进制表示
        for (int i = 0; i < M; ++i) {
            if (dp[i] & target) { // 食物i包含营养j
                if (res[j] == -1) {
                    res[j] = i;
                } else if (count1(dp[i]) > count1(dp[res[j]])) { // 食物i包含的营养比res[j]多
                    res[j] = i;
                }
            }
        }
        if (res[j] == -1) { // 营养j没有被任何食物包含
            if (debug) printf("营养%d没有被任何食物包含\n", j);
            printf("-1\n");
            return 0;
        } else if (debug) {
            printf("营养%d被食物%d包含\n", j, res[j]);
        }
    }

    std::sort(res, res + M);
    printf("%d ", res[0]);
    for (int i = 1; i < M; ++i) {
        if (res[i] != res[i - 1]) {
            printf("%d ", res[i]);
        }
    }
    printf("\n");
    return 0;
}
