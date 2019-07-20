#include <bits/stdc++.h>
using namespace std;
#define MAXN 20005
typedef long long ll;

double mx, sum[MAXN];
int l, r, n, j, t;

int read()
{
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x;
}

int main()
{
    n = read(), l = read(), r = read();
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + read();
        j = i - r, t = i - l;
        if (j < 0)
            j = 0;
        if (t < 0)
            continue;
        while (j <= t)
            mx = max(mx, (sum[i] - sum[j]) / (i - j)), j++;
    }
    printf("%.4lf", mx);
    return 0;
}