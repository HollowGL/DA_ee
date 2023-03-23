#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

bool debug = true;

short N[200005] = {0}, c[200005] = {0};
int n, m;
int countDrop = 0;
int drop[10];

int lowbit(int x) {
    return x&(-x);
}

void addScore(int i, short x) {              // 给序号为i的同学加分
    // for (int j = 0; j < countDrop; j++) {  // 跳过退课的同学
    //     if (i == drop[j]) {
    //         return;
    //     }
    // }
    while (i <= n) {
        c[i] += x;
        i += lowbit(i);
    }
}

int sum(int r, int l) {                   // 求出序号r-l之间的总成绩
    int res1 = 0;
    r -= 1;
    while (r > 0) {
        res1 += c[r];
        r -= lowbit(r);
    }
    int res2 = 0;
    while (l > 0) {
        res2 += c[l];
        l -= lowbit(l);
    }
    return res2 - res1;
}

int restore(int t) {                      // 还原退课前的序号
    for (int i = 0; i < countDrop; i++) {
        if (t >= drop[i]) {
            t++;
        }
    }
    return t;
}

// int sumDrop(int r, int l) {               // 给定区间，求出因退课而多算的人数
//     int count = 0;
//     for (int i = 0; i < countDrop; i++) {
//         if (r < drop[i] && l > drop[i]) {
//             count++;
//         }
//     }
//     return count;
// }

int main() {
    if (debug) {
        freopen("data.in", "r", stdin);
    }

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &N[i]);
        addScore(i, N[i]);
    }

    int flag, t1, t2;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &flag);
        if (flag == 1) {
            scanf("%d%d", &t1, &t2);

            if (debug) {
                printf("指令%d 序号%d修改分数为%d >>> ", flag, t1, t2);
            }
            t1 = restore(t1);
            t2 = restore(t2);
            addScore(t1, t2 - N[t1]);
            N[t1] = t2;   // 初始分数列表也需改变

            if (debug) {
                printf("序号%d修改分数为%d\n", t1, t2);
            }
        }
        else if (flag == 2) {
            scanf("%d%d", &t1, &t2);
            float len = t2 - t1 + 1;
            if (debug) {
                printf("指令%d 计算%d-%d平均成绩 >>> ", flag, t1, t2);
            }

            t1 = restore(t1);
            t2 = restore(t2);
            // float avg = sum(t1, t2) / (t2 - t1 + 1.0 - sumDrop(t1, t2));
            float avg = sum(t1, t2) / len;  // 提前记录长度即可

            if (debug) {
                printf("计算%d-%d平均成绩\n", t1, t2);
                cout << "sum: " << sum(t1, t2) << "    popu: " << /*t2 - t1 + 1.0 - sumDrop(t1, t2)*/len << endl;
            }
            printf("%.3f\n", avg);
        }
        else {
            scanf("%d", &t1);
            if (debug) {
                printf("指令%d 序号%d退课 >>> ", flag, t1);
            }

            t1 = restore(t1);
            addScore(t1, -N[t1]);
            drop[countDrop] = t1;
            countDrop++;
            sort(drop, drop + countDrop);
            N[t1] = 0;        // 修改退课的分数为0，但是不影响其它结果

            if (debug) {
                printf("序号%d退课\n", t1);
                cout << "退课序号: ";
                for (int i = 0; i < countDrop; i++) {
                    cout << drop[i] << " ";
                }
                cout << endl;
            }
        }

        if (debug) {
            cout << "树状分数：";
            for (int i = 1; i <= n; i++) {
                cout << c[i] << " ";
            }
            cout << "   实际分数：";
            for (int i = 1; i <= n; i++) {
                cout << N[i] << " ";
            }
            cout << endl;
            cout << "=======================================" << endl;
        }
    }

    return 0;
}