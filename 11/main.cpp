#include<cstdio>
#include<cmath>
#include<algorithm>

bool debug = true;

struct point {
    int x, y;
    bool operator==(point p) const { return x == p.x && y == p.y; }
};

bool cmp(point a, point b) {
    if (a.y == b.y && a.x < b.x) return true;
    else if (a.y < b.y) return true;
    return false;
}

bool xcross(point a, point b, point c) {
    return (a.x - c.x) * (b.y - c.y) >= (b.x - c.x) * (a.y - c.y);
}

point node[100005];
int num[100005];
point dedup[100005];


int main() {
    if (debug) freopen("./data.in", "r", stdin);

    int n0, n, total;
    scanf("%d", &total);

    for (int cur = 0; cur < total; ++cur) {
        scanf("%d", &n0);
        for (int i = 0; i < n0; ++i) {
            scanf("%d%d", &node[i].x, &node[i].y);
        }
        std::sort(node,node + n0,cmp);

        if (debug) {
            printf("排序之后：n0 = %d\n", n0);
            for (int i = 0; i < n0; ++i) {
                printf("(%d, %d) ", node[i].x, node[i].y);
            }
            printf("\n");
        }

        // 去重
        dedup[0].x = node[0].x;
        dedup[0].y = node[0].y;
        n = 1;
        for (int i = 1; i < n0; ++i) {
            if (node[i] == node[i - 1]) {
                i++;
                if (i == n0) break;
            }
            dedup[n].x = node[i].x;
            dedup[n].y = node[i].y;
            n++;
        }

        if (debug) {
            printf("去重之后：n = %d\n", n);
            for (int i = 0; i < n; ++i) {
                printf("(%d, %d) ", dedup[i].x, dedup[i].y);
            }
            printf("\n");
        }

        num[0]=0; num[1]=1;
        int top = 1;
        for (int i = 2; i < n; ++i) {
            while (top > 1 && xcross(dedup[i], dedup[num[top]], dedup[num[top - 1]]))
                top--;
            top++;
            num[top] = i;
        }
        int basic = top;
        for (int i = n - 2; i >= 0; --i) {
            while (top > basic && xcross(dedup[i], dedup[num[top]], dedup[num[top - 1]]))
                top--;
            top++;
            num[top] = i;
        }

        if (debug) {
            printf("计算凸包：\n");
            for (int i = 0; i < top; ++i) {
                printf("(%d, %d) ", dedup[num[i]].x, dedup[num[i]].y);
            }
            printf("\n");
            printf("\n");
        }
    }

    return 0;
}
