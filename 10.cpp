#include <cstdio>

bool debug = false;

double getElm(double **A, int i, int j) {
    return A[i][j];
}


int main() {

    if (debug) freopen("data.in", "r", stdin);

    int m, zeroCnt;
    scanf("%d%d", &m, &zeroCnt);

    int *b = new int[m];
    double **A = new double*[m];
    for (int i = 0; i < m; ++i) {
        A[i] = new double[m];
    }

    for (int cnt = 0; cnt < m * m - zeroCnt; ++cnt) {
        int i, j;
        double val;
        scanf("%d%d%lf", &i, &j, &val);
        A[i][j] = val;
    }






    return 0;
}