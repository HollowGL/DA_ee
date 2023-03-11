#include <cstdio>
#include <vector>
using namespace std;

const int mod = 9973;
const vector<vector<int>> a = {{1, 1}, {1, 0}};

// 矩阵乘法
vector<vector<int>> mat_mul(vector<vector<int> a, vector<vector<int>> b) {
    vector<vector<int>> c(2, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < m; ++k) {
                C[i][j] += (A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return c;
}

// 矩阵快速幂
vector<vector<int>> mat_pow(int n) {
    if (n == 0) {
        return {{1, 0}, {0, 1}};
    }
    vector<vector<int>> res = mat_pow(a, n / 2);
    res = mat_mul(res, res);
    if (n % 2 == 1) {
        res = mat_mul(res, a);
    }
    return res;
}

int main() {

    int n;
    scanf("%d", &n);

    vector<vector<int>> res = mat_pow(n - 1);
    printf("%d ", res);


    return 0;
}