#include <bits/stdc++.h>
using namespace std;
int n, sum;

inline int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

struct meeting
{
    int l, r;
} m[100005], last;

inline bool comp(meeting x, meeting y)
{
    return x.r < y.r;
}

int main()
{
    scanf("%d", &n);
    int x, y;
    char c;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%c%d", &x, &c, &y);
        m[i].l = x * 100 + y;
        scanf("%d%c%d", &x, &c, &y);
        m[i].r = x * 100 + y;
    }
    sort(m + 1, m + n + 1, comp);
    for (int i = 1; i <= n; i++)
        if (last.r <= m[i].l)
        {
            sum++;
            last = m[i];
        }
    printf("%d", sum);
    return 0;
}