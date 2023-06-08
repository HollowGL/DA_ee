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
Food food[65540];

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
    ushort check = 0;
    for (int i = 0; i < M; ++i) {
        food[i].index = i;
        food[i].nutrients = binFromList(Mi[i]);
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
    ushort nutrition_covered = 0; // 已选择食物的营养与所需营养交集
    ushort target_copy = target;
    while (target) {
        int bestFood = 0;
        for (int i = 0; i < M; ++i) {
            int cur_covered = target & food[i].nutrients;  // 当前食物营养与所需营养交集
            if (count1(cur_covered) >= count1(nutrition_covered)) {
                nutrition_covered = cur_covered;
                bestFood = i;
            } 
            // else if (count1(cur_covered) == count1(nutrition_covered)) {
            //     if (count1(food[i].nutrients) > count1(food[bestFood].nutrients)) {
            //         nutrition_covered = cur_covered;
            //         bestFood = i;
            //     }
            // }
        }

        target ^= nutrition_covered;
        resList[p] = food[bestFood].index;
        p++;
        nutrition_covered = 0;
    }

    // 删除多余食物
    // 似乎没有用
    bool *exist = new bool[65540];
    for (int i = 0; i < p; ++i) {
        exist[i] = true;
    }
    for (int i = 0; i < p; ++i) {
        exist[resList[i]] = false;
        int cur = 0;
        for (int j = 0; j < p; ++j) {
            if (exist[resList[j]]) {
                cur |= food[j].nutrients;
            }
        }
        if (!satisfy(cur, target_copy)) {
            exist[resList[i]] = true;
        }
    }

    std::sort(resList, resList + p);
    for (int i = 0; i < p && exist[resList[i]]; ++i) {
        printf("%d ", resList[i]);
    }

    delete[] exist;
    return 0;
}
