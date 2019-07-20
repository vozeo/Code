#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 3005;
int a, h, n, m, lo[N], stk[N], sum[N];
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep (i, 1, n) {
        h = 0;
        rep (j, 1, m) {
            cin >> a;
            if (!a) lo[j] = i;
            while (lo[j] > lo[stk[h]] && h) --h;
            stk[++h] = j;
            sum[h] = sum[h - 1] + (i - lo[j]) * (stk[h] - stk[h - 1]);
            ans += sum[h];
        }
    }
    cout << ans << endl;
}
