#include <cstdio>

bool debug = false;
typedef unsigned short ushort;


int main() {

    if (debug) freopen("./data.in", "r", stdin);


    ushort usMax = 0xffff;
    ushort us0 = 1 << 0;
    ushort us1 = 1 << 1;
    ushort us2 = 1 << 2;
    ushort a = 0x000f;

    printf("%d", a & us2);




    return 0;
}
