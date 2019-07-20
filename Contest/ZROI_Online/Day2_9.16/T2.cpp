#include <bits/stdc++.h>
using namespace std;
#define N 500005
int l, r, n, ans, sum, a[N], b[N];

template <class T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    x *= f;
}

int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        l = i, r = i;
        while (!(a[l] % a[i]) && l >= 1)
            l--;
        while (!(a[r] % a[i]) && r <= n)
            r++;
        l++, r--;
        b[l] = max(b[l], r - l);
        ans = max(ans, r - l);
    }
    for (int i = 1; i <= n; ++i)
        if (ans == b[i])
            sum++;
    printf("%d %d\n", sum, ans);
    for (int i = 1; i <= n; ++i)
        if (ans == b[i])
            printf("%d ", i);
    return 0;
}