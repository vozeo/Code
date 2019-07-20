#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

int a[105], b[105];
long long f[1005];

int main() {
    int t, m;
    ios::sync_with_stdio(false);
    cin >> t >> m;
    rep (i, 1, m)
        cin >> a[i] >> b[i];
    rep (i, 1, m)
        per (j, t, a[i])
            f[j] = max(f[j], f[j - a[i]] + b[i]);
    cout << f[t] << endl;
}
