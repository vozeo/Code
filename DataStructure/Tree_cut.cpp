#include <cstdio>
#include <cstring>
#include <algorithm>
#define lc o << 1
#define rc o << 1 | 1
using namespace std;
const int maxn = 60010;
const int inf = 2e9;
int n, a, b, w[maxn], q, u, v;
int cur, h[maxn], nxt[maxn], p[maxn];
int siz[maxn], top[maxn], son[maxn], dep[maxn], fa[maxn], tid[maxn], rnk[maxn], cnt;
char op[10];
inline void add_edge(int x, int y)
{
    cur++;
    nxt[cur] = h[x];
    h[x] = cur;
    p[cur] = y;
}
struct SegTree
{
    int sum[maxn * 4], maxx[maxn * 4];
    void build(int o, int l, int r)
    {
        if (l == r)
        {
            sum[o] = maxx[o] = w[rnk[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        sum[o] = sum[lc] + sum[rc];
        maxx[o] = max(maxx[lc], maxx[rc]);
    }
    int query1(int o, int l, int r, int ql, int qr) //max
    {
        if (l > qr || r < ql)
            return -inf;
        if (ql <= l && r <= qr)
            return maxx[o];
        int mid = (l + r) >> 1;
        return max(query1(lc, l, mid, ql, qr), query1(rc, mid + 1, r, ql, qr));
    }
    int query2(int o, int l, int r, int ql, int qr) //sum
    {
        if (l > qr || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return sum[o];
        int mid = (l + r) >> 1;
        return query2(lc, l, mid, ql, qr) + query2(rc, mid + 1, r, ql, qr);
    }
    void update(int o, int l, int r, int x, int t)
    {
        if (l == r)
        {
            maxx[o] = sum[o] = t;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(lc, l, mid, x, t);
        else
            update(rc, mid + 1, r, x, t);
        sum[o] = sum[lc] + sum[rc];
        maxx[o] = max(maxx[lc], maxx[rc]);
    }
} st;
void dfs1(int o, int fat)
{
    son[o] = -1;
    siz[o] = 1;
    for (int j = h[o]; j; j = nxt[j])
        if (!dep[p[j]])
        {
            dep[p[j]] = dep[o] + 1;
            fa[p[j]] = o;
            dfs1(p[j], o);
            siz[o] += siz[p[j]];
            if (son[o] == -1 || siz[p[j]] > siz[son[o]])
                son[o] = p[j];
        }
}
void dfs2(int o, int t)
{
    top[o] = t;
    cnt++;
    tid[o] = cnt;
    rnk[cnt] = o;
    if (son[o] == -1)
        return;
    dfs2(son[o], t);
    for (int j = h[o]; j; j = nxt[j])
        if (p[j] != son[o] && p[j] != fa[o])
            dfs2(p[j], p[j]);
}
int querymax(int x, int y)
{
    int ret = -inf, fx = top[x], fy = top[y];
    while (fx != fy)
    {
        if (dep[fx] >= dep[fy])
            ret = max(ret, st.query1(1, 1, n, tid[fx], tid[x])), x = fa[fx];
        else
            ret = max(ret, st.query1(1, 1, n, tid[fy], tid[y])), y = fa[fy];
        fx = top[x];
        fy = top[y];
    }
    if (x != y)
    {
        if (tid[x] < tid[y])
            ret = max(ret, st.query1(1, 1, n, tid[x], tid[y]));
        else
            ret = max(ret, st.query1(1, 1, n, tid[y], tid[x]));
    }
    else
        ret = max(ret, st.query1(1, 1, n, tid[x], tid[y]));
    return ret;
}
int querysum(int x, int y)
{
    int ret = 0, fx = top[x], fy = top[y];
    while (fx != fy)
    {
        if (dep[fx] >= dep[fy])
            ret += st.query2(1, 1, n, tid[fx], tid[x]), x = fa[fx];
        else
            ret += st.query2(1, 1, n, tid[fy], tid[y]), y = fa[fy];
        fx = top[x];
        fy = top[y];
    }
    if (x != y)
    {
        if (tid[x] < tid[y])
            ret += st.query2(1, 1, n, tid[x], tid[y]);
        else
            ret += st.query2(1, 1, n, tid[y], tid[x]);
    }
    else
        ret += st.query2(1, 1, n, tid[x], tid[y]);
    return ret;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d%d", &a, &b), add_edge(a, b), add_edge(b, a);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    dep[1] = 1;
    dfs1(1, -1);
    dfs2(1, 1);
    st.build(1, 1, n);
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s%d%d", op, &u, &v);
        if (!strcmp(op, "CHANGE"))
            st.update(1, 1, n, tid[u], v);
        if (!strcmp(op, "QMAX"))
            printf("%d\n", querymax(u, v));
        if (!strcmp(op, "QSUM"))
            printf("%d\n", querysum(u, v));
    }
    return 0;
}