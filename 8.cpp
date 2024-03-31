#include <cstdio>
#include <cmath>

bool debug = false;

typedef struct OLNode {
    int i, j;
    double e;
    OLNode *right, *down;
}OLNode, *OLink;

struct CrossList {
    OLink *rhead, *chead;
    int m, n, numCnt;
};

void CreateMatrix(CrossList *M, int m, int cnt);
void display(CrossList M);
void gaussSeidel(CrossList *M, double *x, double *b, int m);


int main() {

    if (debug) freopen("./data.in", "r", stdin);

    int m, numCnt;
    scanf("%d%d", &m, &numCnt);

    CrossList M;
    M.rhead = nullptr;
    M.chead = nullptr;
    CreateMatrix(&M, m, numCnt);
    if (debug) {
        printf("输出矩阵M:\n");
        display(M);
    }

    double *b = new double[m];
    double *x = new double[m];
    for (int i = 0; i < m; ++i) {
        scanf("%lf", &b[i]);
        x[i] = 0.0;
    }

    gaussSeidel(&M, x, b, m);

    delete[] b;
    delete[] x;
    return 0;
}

void CreateMatrix(CrossList *M, int m, int cnt) {
    OLNode *p = nullptr, *q = nullptr;
    M->m = m;
    M->n = m;
    M->numCnt = cnt;

    M->rhead = new OLink[m];
    M->chead = new OLink[m];
    for (int i = 0; i < m; ++i) {
        M->rhead[i] = nullptr;
    }
    for (int i = 0; i < m; ++i) {
        M->chead[i] = nullptr;
    }
    for (int k = 0; k < cnt; ++k) {
        int i, j;
        double e;
        scanf("%d%d%lf", &i, &j, &e);
        p = new OLNode;
        p->i = i;
        p->j = j;
        p->e = e;

        //如果第 i 行没有非 0 元素，或者第 i 行首个非 0 元素位于当前元素的右侧，直接将该元素放置到第 i 行的开头
        if (M->rhead[i] == nullptr || M->rhead[i]->j > j) {
            p->right = M->rhead[i];
            M->rhead[i] = p;
        } else { // 链接到目标位置
            for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right);
            p->right = q->right;
            q->right = p;
        }
        if (M->chead[j] == nullptr || M->chead[j]->i > i) {
            p->down = M->chead[j];
            M->chead[j] = p;
        } else {
            for (q = M->chead[j]; (q->down) && q->down->i < i; q = q->down);
            p->down = q->down;
            q->down = p;
        }
    }
}

void display(CrossList M) {
    int i,j;
    //一行一行的输出
    for (i = 0; i < M.m; i++) {
        //如果当前行没有非 0 元素，直接输出 0
        if (nullptr == M.rhead[i]) {
            for (j = 0; j < M.n; j++) {
                printf("0 ");
            }
            putchar('\n');
        }
        else
        {
            int n = 0;
            OLink p = M.rhead[i];
            //依次输出每一列的元素
            while (n < M.n) {
                if (!p || (n < p->j) ) {
                    printf("0 ");
                }
                else
                {
                    printf("%f ", p->e);
                    p = p->right;
                }
                n++;
            }
            putchar('\n');
        }
    }
}

void gaussSeidel(CrossList *M, double *x, double *b, int m) {
    double x0[m] = {0.0};
    int k = 0;
    do {
        for (int i = 0; i < m; i++) {
            double sum = b[i];
            OLink p = M->rhead[i];
            while (p != nullptr && p->j < i) {
                sum -= p->e * x[p->j];
                p = p->right;
            }
            double diag = p->e;
            p = p->right;
            while (p != nullptr) {
                sum -= p->e * x[p->j];
                p = p->right;
            }

            x[i] = sum / diag;
            x0[i] = x[i];
        }
        k++;
    } while (k <= 20);
    
    for (int i = 0; i < m; ++i) {
        printf("%.10lf\n", x[i]);
    }
}