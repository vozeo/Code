#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 300005;
int n, m, Q, len;
int X[N], Y[N], sol[N];
int T[N + N];
ll Num[N + N];
vector<ll> a[N];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int x, y, id;
} A[N];
bool cmp(node a, node b)
{
    if (a.x != b.x)
        return a.x < b.x;
    return a.id < b.id;
}
void modify(int k, int tot)
{
    for (int i = k; i <= len; i += i & (-i))
        T[i] += tot;
}
int query(int k)
{
    int res = 0;
    for (int i = k; i; i -= i & (-i))
        res += T[i];
    return res;
}
int search(int tot)
{
    int l = 1, r = len, res = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (query(mid) >= tot)
        {
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return res;
}
int main()
{
    n = read();
    m = read();
    Q = read();
    len = max(n, m) + Q;
    for (int i = 1; i <= Q; i++)
    {
        A[i].x = X[i] = read();
        A[i].y = Y[i] = read();
        A[i].id = i;
    }
    sort(A + 1, A + Q + 1, cmp);
    for (int i = 1; i <= len; i++)
        modify(i, 1);
    int pre = 1;
    for (int i = 2; i <= Q + 1; i++)
        if (A[i].x != A[i - 1].x)
        {
            for (int j = pre; j < i; j++)
                if (A[j].y < m)
                {
                    sol[A[j].id] = search(A[j].y);
                    modify(sol[A[j].id], -1);
                }
            for (int j = pre; j < i; j++)
                if (A[j].y < m)
                    modify(sol[A[j].id], 1);
            pre = i;
        }
    for (int i = 1; i <= Q; i++)
    {
        ll ans;
        int k = search(X[i]);
        if (k <= n)
            ans = (ll)k * m;
        else
            ans = Num[k - n];
        modify(k, -1);
        if (Y[i] < m)
        {
            a[X[i]].push_back(ans);
            if (sol[i] < m)
                ans = (ll)(X[i] - 1) * m + sol[i];
            else
                ans = a[X[i]][sol[i] - m];
        }
        Num[i] = ans;
        printf("%lld\n", ans);
    }
    return 0;
}