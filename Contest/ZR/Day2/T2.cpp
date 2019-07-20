#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;
#define N 500005

int n, tot, head[N * 2], ver[N * 2], Next[N], d[N], fa[N];
ll ans[N];
bool u[N];

int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        c = getchar(), x = x * 10 + c - '0';
    return x;
}

void add(int x, int y)
{
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void init()
{
    memset(u, 0, sizeof(u));
    memset(fa, 0, sizeof(fa));
    memset(d, 0, sizeof(d));
}

void bfs(int cur)
{
    queue<int> q;
    q.push(cur);
    fa[cur] = cur;
    u[cur] = true;
    while (q.size())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = Next[i])
        {
            int y = ver[i];
            if (u[y])
                continue;
            fa[y] = x;
            u[y] = true;
            d[y] = d[x] + 1;
            q.push(y);
        }
    }
    rep(i, 1, n)
    {
        if (d[i] % 2)
            continue;
        int x = i;
        while (x != cur)
        {
            x = fa[x];
            if (d[x] == d[i] >> 1)
            {
                ans[x]++;
                break;
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    int x, y;
    rep(i, 1, n - 1)
    {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    rep(i, 1, n)
    {
        init();
        bfs(i);
    }
    rep(i, 1, n)
        printf("%lld ", (ans[i] >> 1) + 1);
    return 0;
}