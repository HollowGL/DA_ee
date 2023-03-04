#include <cstdio>

int fib(int);
int m_fib(int);

int main() {
    int n;
    scanf("%d", &n);
    int a[20];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) 
        printf("%d\n", m_fib(a[i]));
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

int m_fib(int n) {
    if (n < 10000000)
        return fib(n);
    if (n % 2 == 1) {
        int x = m_fib((n + 1) / 2);
        int y = m_fib((n - 1) / 2);
        return (x * x + y * y) % 9973;
    }
    else {
        int x = m_fib(n / 2);
        int y = m_fib(n / 2 - 1);
        return (x * (2 * y + x)) % 9973;
    }
}