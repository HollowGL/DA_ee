/*
贪心
*/

#include <cstdio>
#include <algorithm>

bool debug = false;

// 实际上是近似最优而不一定是全局最优
/* 如以下案例：N=6, M=5
6 5 4 3 3 1 1
1 2 3 4 5 6
1 2 3 4
1     4   6
  2 3   5
        5
          6
expect: 1 2
result: 0 3 4 or 0 1 2
*/

struct Food {
    int index;
    int nutrients;
};

bool satisfy(int s, int t) {
    return (s | t) == s;
}

int N, M, target = 0;
int Mi[65540], Ni[16], resList[16];
Food food[65540];

int main() {
    if (debug) freopen("./data.in", "r", stdin);

    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d", &Mi[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &Ni[i]);
        target |= 1 << (Ni[i] - 1);
    }
    int check = 0;
    for (int i = 0; i < M; ++i) {
        food[i].index = i;
        food[i].nutrients = 0;
        for (int j = 0; j < Mi[i]; ++j) {
            int temp = 0;
            scanf("%d", &temp);
            food[i].nutrients |= 1 << (temp - 1);
        }
        check |= food[i].nutrients;
    }

    if (debug) {
        for (int i = 0; i < M; ++i) {
            printf("第%d种食物含有营养%x\n", i, food[i].nutrients);
        }
        printf("营养需求为: ");
        for (int i = 0; i < N; ++i) {
            printf("%d ", Ni[i]);
        }
        printf("%x\n", target);
    }

    if (!(satisfy(check, target))) {
        printf("-1\n");
        return 0;
    }

    int p = 0;
    int nutrition_covered = 0; // 已选择食物的营养与所需营养交集
    while (target) {
        int bestFood = -1;
        int nutrition_covered = -1; // 已选择食物的营养与所需营养交集的营养
        for (int i = 0; i < M; ++i) {
            // __builtin_popcount: 计算二进制中1的个数
            int cur_covered = __builtin_popcount(target & food[i].nutrients);  // 当前食物营养与所需营养交集
            if (cur_covered >= nutrition_covered) {
                nutrition_covered = cur_covered;
                bestFood = i;
            } 
        }

        if (bestFood != -1) {
            target &= ~food[bestFood].nutrients;
            resList[p] = food[bestFood].index;
            p++;
        }
    }

    std::sort(resList, resList + p);
    for (int i = 0; i < p; ++i) {
        printf("%d ", resList[i]);
    }


    return 0;
}
