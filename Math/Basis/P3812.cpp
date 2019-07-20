#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
int cnt;
ll p[100];

void get(ll x) {
    per (i, 52, 0) {
        if (!(x >> i))
            continue;
        if (!p[i]) {
            ++cnt, p[i] = x;
            return;
        }
        x ^= p[i];
    }
}

char s[100];

int main() {
    int n, m;
    ll x;
    scanf("%d%d", &n, &m);
    /* cout << m << endl; */
    rep (i, 1, m) {
        cin >> s;
        x = 0;
        rep (j, 0, n - 1)
            if (s[j] == 'O')
                x += (1ll << (n - 1 - j));
        /* cout << x << endl; */
        get(x);
    }
    /* ll ans = 0, res = 1; */
    /* per (i, 52, 0) */
    /*     if ((ans ^ p[i]) > ans) */
    /*         ans ^= p[i], res = res * 2 % 2008; */
    printf("%lld\n", (1ll << cnt) % 2008);
}
