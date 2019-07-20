#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int ans, res, a[20], num[5000];

int main() {
    freopen("determinant.in", "w", stdout);
    int n = 9;
    rep (i, 1, 9)
        a[i] = i;
    ans = 0;
    do {
        res = a[1] * a[5] * a[9] + a[2] * a[6] * a[7] + a[3] * a[4] * a[8] - a[3] * a[5] * a[7] - a[2] * a[4] * a[9] - a[1] * a[6] * a[8];
        ans = max(ans, res);
        ++num[res + 412];
        if (res == 412) {
            rep (i, 1, n) {
                cout << a[i] << " ";
                if (i % 3 == 0)
                    cout << endl;
            }
            cout << endl;
        }
    } while (next_permutation(a + 1, a + n + 1));

    rep (i, 0, 1000)
        if (num[i]) cout << i - 412 << " ";
    cout << ans << endl;
}
