#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e6 + 5, P = 998244353;
typedef long long ll;
int type, tot, cnt;
ll las, b[N];

struct Mat {
    ll a[2][2];
    Mat() { a[0][0] = a[1][1] = a[0][1] = a[1][0] = 0; }
    Mat(ll x) {
        if (x) a[0][0] = x, a[1][0] = a[0][1] = 1, a[1][1] = 0;
        else a[0][0] = a[1][1] = 1, a[0][1] = a[1][0] = 0;
    }
    Mat(ll x, ll y) {
        a[0][0] = x, a[0][1] = y, a[1][0] = a[1][1] = 0;
    }
    Mat operator * (const Mat &r) const {
        Mat c;
        rep (i, 0, 1)
            rep (j, 0, 1)
                rep (k, 0, 1)
                    c.a[i][j] = (c.a[i][j] + a[i][k] * r.a[k][j]) % P;
        return c;
    }
} t[N], Ret;

struct Node {
    Node *lc, *rc;
    Mat v;
    Node() {}
    Node(Node *l, Node *r) : lc(l), rc(r) {
        maintain();
    }
    Node(ll x) : v(Mat(x)) {}
    void maintain() {
        v = rc->v * lc->v;
    }
    void modify(int l, int r, int p, ll x) {
        if (l == r) {
            v = Mat(x);
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) lc->modify(l, mid, p, x);
        else rc->modify(mid + 1, r, p, x);
        maintain();
    }
    void query(int l, int r, int nl, int nr) {
        if (l <= nl && nr <= r) {
            Ret = Ret * v;
            return;
        }
        int mid = (nl + nr) >> 1;
        if (r > mid) rc->query(l, r, mid + 1, nr);
        if (l <= mid) lc->query(l, r, nl, mid);
    }
} tpool[N << 1], *tcur = tpool, *segt = tpool;

Node *build(int l, int r) {
    if (l == r)
        return new (++tcur) Node(b[l]);
    int mid = (l + r) >> 1;
    return new (++tcur) Node(build(l, mid), build(mid + 1, r));
}

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

void cal(int l, int r) {
    if (type) l ^= las, r ^= las;
    Ret = Mat(b[r], 1);
    segt->query(l, r - 1, 1, tot);
    ll x = Ret.a[0][0], y = Ret.a[0][1];
    printf("%lld %lld\n", x, y);
    las = x ^ y;
}

int main() {
    freopen("alone3.in", "r", stdin);
    freopen("alone3.out", "w", stdout);
    int n, m, op, x, y;
    read(n), read(m), read(type);
    tot = n + m, cnt = n;
    rep (i, 1, n)
        read(b[i]);
    segt = build(1, tot);
    rep (i, 1, m) {
        read(op), read(x);
        if (op == 1) {
            if (type) x ^= las;
            b[++cnt] = x, segt->modify(1, tot, cnt, x);
        }
        else read(y), cal(x, y);
    }
}
