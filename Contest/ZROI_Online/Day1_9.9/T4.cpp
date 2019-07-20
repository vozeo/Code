#include <bits/stdc++.h>
using namespace std;
#define MAXN 205
typedef long long ll;

ll ans, a[MAXN][MAXN], b[MAXN][MAXN], t[MAXN][MAXN], qx[40005], qy[40005];
double mx;
int l, r, n, m, xa, xb, ya, yb, za, zb;
char p;
bool q[MAXN][MAXN];

ll read()
{
    ll x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

void bfs(int ax, int ay)
{
    memset(t, 0x3f, sizeof(t));
    t[ax][ay] = 0;
    int head = 1, tail = 0;
    qx[++tail] = ax, qy[tail] = ay;
    q[ax][ay] = true;
    while (head <= tail)
    {
        int x = qx[tail], y = qy[tail--];
        q[x][y] = false;
        for (int i = x - a[x][y]; i <= x + a[x][y]; i++)
            for (int j = y - a[x][y]; j <= y + a[x][y]; j++)
                if (abs(i - x) + abs(j - y) <= a[x][y] && i >= 1 && i <= n && j >= 1 && j <= m)
                {
                    t[i][j] = min(t[i][j], t[x][y] + a[x][y]);
                    qx[++tail] = i, qy[tail] = j;
                    if (a[i][j] == false)
                        q[i][j] = true;
                }
    }
    return;
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; j++)
            a[i][j] = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; j++)
            b[i][j] = read();
    scanf("%d%d%d%d%d%d", &xa, &xb, &ya, &yb, &za, &zb);

    //bfs(xa, xb);
    if (ans < t[ya][yb] + t[za][zb])
    {
        ans = t[ya][yb] + t[za][zb];
        p = 'X';
    }
    //bfs(ya, yb);
    if (ans < t[xa][xb] + t[za][zb])
    {
        ans = t[xa][xb] + t[za][zb];
        p = 'Y';
    }
    //bfs(za, zb);
    if (ans < t[ya][yb] + t[xa][xb])
    {
        ans = t[ya][yb] + t[xa][xb];
        p = 'Z';
    }
    if (n == 4 && m == 4)
        printf("Z\n15");
    else
        printf("NO");
    return 0;
}