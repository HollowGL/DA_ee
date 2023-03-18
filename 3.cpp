// reference: [双指针](https://developer.aliyun.com/article/1137665)

#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {

    int n;
    scanf("%d", &n);
    int *num = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    if (n < 3) {
        printf("%d", 0);
        return 0;
    }

    sort(num, num + n);
    int count = 0;
    vector<vector<int> > v;
    
    for (int i = 0; i < n; i++) {
        if (i > 0 && num[i] == num[i - 1]) {
            continue;
        }
        int left = 0, right = n - 1;
        while (left < right) {
            if (left == i) {
                left++;
                continue;
            }
            if (right == i) {
                right--;
                continue;
            }
            if (num[left] + num[right] < num[i]) {  
                left++;
            } else if (num[left] + num[right] > num[i]) {
                right--;
            } else {
                v.push_back({num[i], num[left], num[right]});
                count++;
                while(left < right && num[left] == num[left + 1])  left++;
                while(left < right && num[right] == num[right - 1])  right--;
                left++;
                right--;
            }      
        }
    }
    printf("%d\n", count);
    for (int i = 0; i < v.size(); i++) {
        printf("%d %d %d    ", v[i][0], v[i][1], v[i][2]);
    }

    return 0;
}
