#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 5e4 + 5;
typedef long long ll;

ll gcd (ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int L, a[N], b[N];
ll sum, s[N], ans[N][2];

struct Qry {
    int l, r, id;
    bool operator < (const Qry &rhs) const {
        return b[l] == b[rhs.l] ? (b[l] & 1 ? r < rhs.r : r > rhs.r) : b[l] < b[rhs.l];
    }
} q[N];


void upd(int c, int p) {
    sum += s[c] * (p << 1) + 1;
    s[c] += p;
}

int l, r, n, m;
ll x, y, g;

int main() {
    freopen("P1494.in", "r", stdin);
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]);
    //L = n / sqrt((m << 1) / 3);
    L = 1.2 * sqrt(n);
    rep (i, 1, n)
        b[i] = (i - 1) / L + 1;
    rep (i, 1, m)
        read(q[i].l), read(q[i].r), q[i].id = i;
    sort(q + 1, q + m + 1);
    l = 1;
    rep (i, 1, m) {
        while (r < q[i].r) upd(a[++r], 1);
        while (r > q[i].r) upd(a[r--], -1);
        while (l < q[i].l) upd(a[l++], -1);
        while (l > q[i].l) upd(a[--l], 1);
        if (q[i].l == q[i].r) {
            ans[q[i].id][0] = 0, ans[q[i].id][1] = 1;
            continue;
        }
        x = sum - (r - l + 1);
        y = 1ll * (r - l + 1) * (r - l);
        g = gcd(x, y);
        ans[q[i].id][0] = x / g, ans[q[i].id][1] = y / g;
    }
    rep (i, 1, m)
        printf("%lld/%lld\n", ans[i][0], ans[i][1]);
}
