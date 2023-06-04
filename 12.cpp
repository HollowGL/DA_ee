#include <cstdio>

bool debug = false;
typedef unsigned short ushort;


int main() {

    if (debug) freopen("./data.in", "r", stdin);


    ushort usMax = 0xffff;
    ushort us0 = 1 << 0;
    ushort us1 = 1 << 1;
    ushort us2 = 1 << 2;
    ushort a = 14;

    printf("%d", a & us0);




    return 0;
}
