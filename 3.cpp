#include <cstdio>
#include <algorithm>

int main() {
    int n;
    double num[3000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &num[i]);
    }
    std::sort(num, num + n);   // 默认从小到大

    int count = 0;
    double old1 = 1, old2 = 1, old3 = 1;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (num[i] + num[j] == num[k] || num[j] + num[k] == num[i] || num[i] + num[k] == num[j]) {
                    if (num[i] != old1 || num[j] != old2 || num[k] != old3) {
                        count++;
                        old1 = num[i];
                        old2 = num[j];
                        old3 = num[k];
                    }
                }

            }
        }
    }
    printf("%d", count);

    return 0;
}