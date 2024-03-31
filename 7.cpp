#include <cstdio>
#include <cmath>

bool debug = false;

double getX(double *array, int n, int i) {
    if (i >= 0 && i < n)
        return array[i];
    return 0;
}


int main() {

    if (debug) freopen("./data.in", "r", stdin);

    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);
    double *x = new double[N];
    double *h = new double[M];
    double *y = new double[N + M - 1];

    for (int i = 0; i < N + M - 1; ++i) {
        scanf("%lf", &y[i]);
    }
    for (int i = 0; i < M; ++i) {
        scanf("%lf", &h[i]);
    }
    for (int i = 0; i < N; i++) {
        x[i] = 0;
    }

    if (debug) {
        // for (int i = 1 - M; i < M + N - 1; ++i) {
        //     printf("%lf, ", getX(x, N, i));
        // }
    }

    // convolution 卷积
    for (int t = 0; t < N; ++t) {
        double convo = 0;
        for (int i = M - 1; i > 0; --i) {
            convo += h[i] * getX(x, N, t - i);

            if (debug) {
                printf("convo = %lf", convo);
            }
        }
        x[t] = (y[t] - convo) / h[0];
        x[t] = round(x[t] * 10000) / 10000; // 保留四位小数

        if (x[t] < 0) { // 解不存在
            printf("%d\n", N);
            return 0;
        }

        if (debug) {
            printf("y[%d]=%lf ", t, y[t]);
            printf("x[%d]=%lf \n\n", t, x[t]);
        }
    }

    // 继续卷积，验证结果（从功利的角度出发，这段没必要）
    // for (int t = N - M + 1; t < N; ++t) {
    //     double convo = 0;
    //     for (int i = M - 1; i >= 0; --i) {
    //         convo += h[i] * getX(x, N, t + M - 1 - i);
    //     }
    //     if (y[t + M - 1] != convo) { // 解不存在
    //         printf("%d\n", N);
    //         return 0;
    //     }
    // }


    if (!debug) {
        for (int t = 0; t < N; ++t) {
            printf("%.4lf ", x[t]);
        }
    }


    delete[] x;
    delete[] h;
    delete[] y;

    return 0;
}
