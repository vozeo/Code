#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <ctime>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<long long, long long> pll;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for (register int i = (int)(j); i <= (int)(k); i++)
#define rrep(i, j, k) for (register int i = (int)(j); i >= (int)(k); i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)

ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

struct Heap
{
    static const int maxn = 1000100;
    int a[maxn], cnt;
    void ins(int x)
    {
        a[++cnt] = x;
        int pre = cnt >> 1, nw = cnt;
        while (a[pre] > a[nw])
        {
            swap(a[pre], a[nw]);
            nw = pre;
            pre = nw >> 1;
            if (!pre)
                break;
        }
    }
    void pop()
    {
        swap(a[1], a[cnt]);
        cnt--;
        int x = 1;
        while (true)
        {
            int ls = x << 1, rs = x << 1 | 1;
            if (ls > cnt)
                break;
            if (a[x] <= a[ls] && (rs > cnt || a[x] <= a[rs]))
                break;
            if ((a[x] > a[ls] && rs > cnt) || (rs <= cnt && a[ls] < a[rs]))
                swap(a[x], a[ls]), x = ls;
            else
                swap(a[x], a[rs]), x = rs;
        }
    }
    int top() { return a[1]; }
} heap;

struct DSU
{
    static const int maxn = 10010;
    int fa[maxn], n;

    void init()
    {
        rep(i, 1, n) fa[i] = i;
    }
    int fp(int x)
    {
        return fa[x] == x ? x : fa[x] = fp(fa[x]);
    }
    void uni(int x, int y)
    {
        x = fp(x);
        y = fp(y);
        if (x != y)
            fa[x] = y;
    }
    void pd(int x, int y)
    {
        x = fp(x);
        y = fp(y);
        puts((x == y) ? "Y" : "N");
    }
} dsu;

struct HASH
{
    static const int hsh = 20020709, mod = 1e9 + 7;
    set<int> s;

    void ins(string x)
    {
        int l = x.size(), ret = 0;
        rep(i, 0, l - 1)
            ret = (ret * 1ll * hsh + x[i]) % mod;
        s.insert(ret);
    }
} hsh;

struct ST_Table
{
    static const int maxn = 100100;
    int mx[maxn][20];
    int a[maxn], n, lg[maxn];

    void init()
    {
        rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
        rep(i, 1, n) mx[i][0] = a[i];
        rep(j, 1, 18)
            rep(i, 1, n)
                if (i + (1 << j) - 1 <= n)
                    mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
    }
    int ask(int l, int r)
    {
        int len = r - l + 1;
        len = lg[len];
        return max(mx[l][len], mx[r - (1 << len) + 1][len]);
    }
} st;

struct BIT
{
    static const int maxn = 500500;
    int a[maxn], n;

    void add(int x, int v)
    {
        while (x <= n)
        {
            a[x] += v;
            x += x & -x;
        }
    }
    void add(int l, int r, int v)
    {
        add(l, v);
        add(r + 1, -v);
    }
    int ask(int x)
    {
        int ret = 0;
        while (x)
        {
            ret += a[x];
            x -= x & -x;
        }
        return ret;
    }
    int ask(int l, int r)
    {
        return ask(r) - ask(l - 1);
    }
} bit;

void work()
{
    bit.n = read();
    int m = read();
    rep(i, 1, bit.n)
    {
        int x = read();
        bit.add(i, i, x);
    }
    rep(i, 1, m)
    {
        int op = read();
        if (op == 1)
        {
            int l = read(), r = read(), x = read();
            bit.add(l, r, x);
        }
        else
        {
            int pos = read();
            printf("%d\n", bit.ask(pos));
        }
    }
}

int main()
{
    work();
}