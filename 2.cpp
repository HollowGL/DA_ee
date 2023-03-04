#include <cstdio>

int fib(int);

int main() {

    int n, max = 0;
    scanf("%d", &n);
    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        // max = a[i] > max ? a[i] : max;
    }

    // int *fib = new int[max + 1];
    // fib[0] = 0;
    // fib[1] = 1;
    // for (int i = 2; i < max + 1; i++) {
    //     fib[i] = (fib[i - 2] + fib[i - 1]) % 9973;
    // }

    // for (int i = 0; i < n; i++) {
    //     printf("%d\n", fib[a[i]]);
    // }
    for (int i = 0; i < n; i++) 
        printf("%d\n", fib(a[i]));

    delete[] a;
    // delete[] fib;
    return 0;
}

int fib(int n) {
    int f1 = 0, f2 = 1, temp;
    for (int i = 0; i < n; i++) {
        temp = f2;
        f2 = (f1 + f2) % 9973;
        f1 = temp;
    }
    return f1;
}