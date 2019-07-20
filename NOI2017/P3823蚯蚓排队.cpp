#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 3e5 + 5, M = 6e5 + 5, P = 998244353;
typedef long long ll;
bool NoT = true, KsO = true;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

ll qpow(ll x, ll b) {
    ll ans = 1;
    for (; b; b >>= 1, x = x * x % P)
        if (b & 1)
            ans = ans * x % P;
    return ans;
}

int fa[N];

int find(int x) {
    while (fa[x] != x)
        x = fa[x] = fa[fa[x]];
    return x;
}

int n, m, a[N], op[M], x[M], y[M], val[N], buc[N];
string s[M];
set<int> qs;

void solve1() {
    ll ans;
    rep (i, 1, m)
        if (op[i] == 3) {
            ans = 1;
            for (unsigned int j = 0; j < s[i].size(); ++j)
                ans = ans * buc[s[i][j] - '0'] % P;
            printf("%lld\n", ans);
        }
}


void solve2() {
    set<int>::iterator it;
    ll cnt;
    rep (i, 1, n)
        fa[i] = i, val[i] = 1, qs.insert(i);
    rep (i, 1, m) {
        if (op[i] == 1) {
            int p = find(x[i]), q = find(y[i]);
            fa[p] = q, val[q] += val[p], qs.erase(p);
        } else {
            cnt = 0;
            for (it = qs.begin(); it != qs.end(); ++it)
                if (val[*it] >= y[i])
                    cnt = (cnt + val[*it] - y[i] + 1) % P;
            printf("%lld\n", qpow(cnt, s[i].size() - y[i] + 1));
        }
    }
}

int main() {
    freopen("P3823.in", "r", stdin);
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]), ++buc[a[i]];
    rep (i, 1, m) {
        read(op[i]);
        if (op[i] == 1)
            read(x[i]), read(y[i]);
        else if (op[i] == 3) {
            cin >> s[i], read(y[i]);
            if (y[i] != 1)
                KsO = false;
        } else if (op[i] == 2)
            read(x[i]), NoT = false;
    }
    if (KsO) solve1();
    else solve2();
}
