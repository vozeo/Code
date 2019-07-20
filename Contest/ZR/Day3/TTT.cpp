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

int n, a[1100000], b[1100000];
bool ans;

int prm[1100000], lp;
int fac[1100000];

int hd[1100000], id[1100000], len[1100000];

struct eq1
{
    int r, p;
} e1[1100000];
struct eq2
{
    int r, p, a;
} e2[7100000];
int l1, l2;
bool operator<(eq2 x, eq2 y) { return x.p < y.p || x.p == y.p && x.a > y.a; }

void init()
{
    FOR(i, 2, 1000000)
    {
        if (!fac[i])
        {
            prm[++lp] = i;
            fac[i] = lp;
        }
        REP(j, lp)
        {
            if (prm[j] * i > 1000000)
                break;
            fac[prm[j] * i] = j;
            if (fac[i] == j)
                break;
        }
    }
}
void readin()
{
    REP(i, n)
    read(a[i]);
    REP(i, n)
    read(b[i]);
    REP(i, n)
    id[i] = len[i] = 0;
    l1 = l2 = 0;
    ans = true;
}
void geteq()
{
    REP(i, n)
    if (!id[i])
    {
        int t(i);
        do
        {
            hd[t] = i, id[t] = ++len[i];
            t = a[t];
        } while (t != i);
    }
    REP(i, n)
    if (hd[b[i]] != hd[i])
    {
        ans = false;
        return;
    }
    else if (len[hd[i]] != 1)
    {
        e1[++l1].r = (id[b[i]] - id[i] + len[hd[i]]) % len[hd[i]], e1[l1].p = len[hd[i]];
    }
}
void solve()
{
    REP(i, l1)
    {
        int t(e1[i].p);
        while (t != 1)
        {
            int p(fac[t]);
            e2[++l2].p = p;
            e2[l2].a = 1;
            while (fac[t] == p)
            {
                t /= prm[p];
                e2[l2].a *= prm[p];
            }
            e2[l2].r = e1[i].r % e2[l2].a;
        }
    }
    sort(e2 + 1, e2 + l2 + 1);
    REP(i, l2 - 1)
    if (e2[i].p == e2[i + 1].p)
    {
        if (e2[i].r % e2[i + 1].a != e2[i + 1].r)
        {
            ans = false;
            return;
        }
    }
}
int main()
{
    init();
    while (scanf("%d", &n) != EOF)
    {
        readin();
        geteq();
        if (!ans)
        {
            puts("No");
            continue;
        }
        solve();
        if (ans)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
