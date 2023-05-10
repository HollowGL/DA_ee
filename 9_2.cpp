#include <cstdio>
#include <ccomplex>

// FFT
void fft(int *x, int n) {
    if (n == 1) return;
    int *x1 = new int[n / 2];
    int *x2 = new int[n / 2];
    for (int i = 0; i < n / 2; i++) {
        x1[i] = x[i * 2];
        x2[i] = x[i * 2 + 1];
    }
    fft(x1, n / 2);
    fft(x2, n / 2);
    for (int i = 0; i < n / 2; i++) {
        x[i] = x1[i] + x2[i];
        x[i + n / 2] = x1[i] - x2[i];
    }
    delete[] x1;
    delete[] x2;
}

// IFFT
void ifft(int *x, int n) {
    if (n == 1) return;
    int *x1 = new int[n / 2];
    int *x2 = new int[n / 2];
    for (int i = 0; i < n / 2; i++) {
        x1[i] = x[i * 2];
        x2[i] = x[i * 2 + 1];
    }
    ifft(x1, n / 2);
    ifft(x2, n / 2);
    for (int i = 0; i < n / 2; i++) {
        x[i] = x1[i] + x2[i];
        x[i + n / 2] = x1[i] - x2[i];
    }
    delete[] x1;
    delete[] x2;
}


int main() {

    int *x = new int[5];
    for (int i = 0; i < 5; i++) {
        x[i] = i;
    }
    fft(x, 5);

    for (int i = 0; i < 5; ++i) {
        printf("%d ", x[i]);
    }
    printf("\n");

    ifft(x, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
    
    return 0;
}