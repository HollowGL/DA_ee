#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

bool debug = true;


int main() {

    if (debug) { freopen("./data.in", "r", stdin); }

    int foldersCnt;
    int filesCnt;

    scanf("%d", &foldersCnt);
    for (int i = 0; i < foldersCnt; i++) {
        scanf("%d", &filesCnt);
        for (int j = 0; j < filesCnt; j++) {
            char c[105];
            scanf("%s", c);

            printf("%s ", c);
        }
    }


    if (debug) {
    }
    printf("%d", foldersCnt);

    return 0;
}