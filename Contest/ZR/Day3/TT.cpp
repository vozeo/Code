#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#define REP(i, n) for (int i = 1; i <= (n); ++i)
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define FEC(p, u) for (edge *p = head[u]; p; p = p->nxt)
using namespace std;
typedef long long LL;
void read(int &x)
{
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    for (x = 0; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - 48;
}

int n, a[1100000], b[1100000], f[1100000], og[2100000];
int *g(og + 1050000);
int t1[1100000], t2[1100000];

void init()
{
    read(n);
    REP(i, n)
    {
        read(a[i]);
        t1[a[i]] = i;
    }
    REP(i, n)
    {
        read(b[i]);
        t2[t1[b[i]]] = i;
    }
}
void work()
{
    ROF(i, n, 1)
    {
        int j = t2[i];
        if (g[i - j - 1])
            f[i] = f[g[i - j - 1]] + g[i - j - 1] - i + 1;
        else
            f[i] = max(n - i + 2, n - j + 1);
        if (g[i - j + 1])
            f[i] = min(f[i], f[g[i - j + 1]] + g[i - j + 1] - i);
        else
            f[i] = min(f[i], max(n - i + 1, n - j + 2));
        g[i - j] = i;
    }
    printf("%d\n", g[0] ? f[g[0]] + g[0] - 1 : n);
}
int main()
{
    init();
    work();
    return 0;
}