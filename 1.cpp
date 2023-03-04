#include <iostream>
#include <cstring>

int main() {

    char num1[200], num2[200];
    scanf("%s %s", num1, num2);

    int len1 = strlen(num1), len2 = strlen(num2);
    if (len1 < 9 && len2 < 9) {
        long long n1 = strtol(num1, NULL, 10);
        long long n2 = strtol(num2, NULL, 10);
        printf("%lld", n1 + n2);
        return 0;
    }

    char num3[200], num4[200];
    for (int i = 0; i < len1; i++) 
        num3[i] = num1[len1 - i - 1];
    for (int i = 0; i < len2; i++) 
        num4[i] = num2[len2 - i - 1];

    int maxlen;
    if (len1 > len2) {
        maxlen = len1;
        for (int i = len2; i < maxlen; i++) 
            num4[i] = '0';
    }
    else {
        maxlen = len2;
        for (int i = len1; i < maxlen; i++)
            num3[i] = '0';
    }
    
    int temp = 0;
    num3[maxlen] = '0';
    for (int i = 0; i < maxlen; i++) {
        temp = num3[i] + num4[i] - '0' - '0';
        num3[i] = temp % 10 + '0';
        num3[i + 1] += temp / 10;   // 注意num3[maxlen]本应该是'\0'，因此需要将其先初始化为'0'，并且在后面再单独判断是否有进位
    }
    
    int i = num3[maxlen] == '1' ? 0 : 1;
    for (; i <= maxlen; i++)
        printf("%c", num3[maxlen - i]);

    return 0;
}