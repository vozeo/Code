#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("data.in", "w", stdout);
    char a[7][5] = {"add", "set", "sum", "max", "min"};
    srand(time(NULL));
    int n = 100000;
    printf("100000 100000\n");
    for (int i = 1; i <= n; ++i)
        printf("%lld ", (long long)rand() / 1000);
    printf("\n");
    long long x, y;
    int t;
    for (int i = 1; i <= n; ++i) {
        x = (long long)rand() * 100000 / RAND_MAX;
        y = (long long)rand() * 100000 / RAND_MAX;
        if (x > y)
            swap(x, y);
        t = rand() % 5;
        printf("%s %lld %lld ", a[t], x, y);
        if (t <= 1)
            printf("%lld", (long long)rand() / 1000);
        printf("\n");
    }
}