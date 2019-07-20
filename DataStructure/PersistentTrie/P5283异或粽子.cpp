#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 5e5 + 5, W = 31;
ll a[N];

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getc()));
    for (x = ch - '0'; isdigit(ch = getc()); x = x * 10 + ch - '0');
}
/*
template<typename T, typename... Args>
void read(T &x, Args &... args) {
    read(x);
    read(args...);
}
*/
struct Trie {
    int sum;
    Trie *ch[2];
    Trie() {}
    Trie(Trie *p) {
        if (p) *this = *p;
    }
} tpool[N * W * 2], *tcur = tpool, *root[N];

void insert(Trie *&o, ll x, int d = W) {
    o = new (++tcur) Trie(o), ++o->sum;
    if (d < 0) return;
    insert(o->ch[(x >> d) & 1], x, d - 1);
}

ll query(Trie *o, ll x, int k) {
    int v, s;
    ll res = 0;
    for (int d = W; ~d; --d) {
        if (!o) break;
        v = (x >> d) & 1, s = o->ch[v ^ 1] ? o->ch[v ^ 1]->sum : 0;
        if (k <= s)
            o = o->ch[v ^ 1], res += 1ll << d;
        else o = o->ch[v], k -= s;
    }
    return res;
}

ll query2(Trie *o, ll x, int k, int d = W) {
    if (d < 0) return 0;
    int v = (x >> d) & 1, s = o->ch[v ^ 1] ? o->ch[v ^ 1]->sum : 0;
    if (k <= s)
        return query2(o->ch[v ^ 1], x, k, d - 1) + (1ll << d);
    else return query2(o->ch[v], x, k - s, d - 1);
}

struct Sta {
    int pos, rk;
    ll val;
    Sta() {}
    Sta(int x, int y, ll z) : pos(x), rk(y), val(z) {}
    bool operator < (const Sta &rhs) const {
        return val < rhs.val;
    }
};

priority_queue<Sta> q;

int main() {
    freopen("19.in", "r", stdin);
    int n, K;
    read(n), read(K);
    rep (i, 1, n)
        read(a[i]), a[i] ^= a[i - 1], insert(root[i] = root[i - 1], a[i - 1]);
    rep (i, 1, n)
        q.push(Sta(i, 1, query(root[i], a[i], 1)));
    ll ans = 0;
    rep (i, 1, K) {
        Sta x = q.top();
        q.pop(), ans += x.val;
        if (x.rk < x.pos)
            q.push(Sta(x.pos, x.rk + 1, query(root[x.pos], a[x.pos], x.rk + 1)));
    }
    printf("%lld\n", ans);
}
