#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1005, P = 1e9 + 7;
typedef long long ll;
ll n, lo[N], sum[N], stk[N], a[N][N], f[N][N];
ll And, Or, Tot;

ll work(int x) {
    ll ans = 0, h;
    memset(lo, 0, sizeof lo);
    memset(sum, 0, sizeof sum);
    rep (i, 1, n) {
        h = 0;
        rep (j, 1, n) {
            if (f[i][j] == x)
                lo[j] = i;
            while (lo[j] > lo[stk[h]] && h)
                --h;
            stk[++h] = j;
            sum[h] = sum[h - 1] + (i - lo[j]) * (stk[h] - stk[h - 1]);
            ans += sum[h];
        }
    }
    return x ? Tot - ans : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    Tot = n * n * (n + 1) * (n + 1) / 4;
    rep (i, 1, n)
        rep (j, 1, n)
            cin >> a[i][j];
    rep (i, 0, 31) {
        rep (j, 1, n)
            rep (k, 1, n)
                f[j][k] = (a[j][k] >> i) & 1;
        And = (And + work(0) % P * ((1 << i) % P) % P) % P;
        Or = (Or + work(1) % P * ((1 << i) % P) % P) % P;
    }
    cout << And << " " << Or << endl;
}
