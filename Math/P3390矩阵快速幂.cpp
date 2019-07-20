#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 105, P = 1e9 + 7;

struct Matrix {
    int n, m;
    ll a[N][N];
    Matrix() {}
    Matrix(int x, int y) : n(x), m(y) {
        memset(a, 0, sizeof a);
    }
    Matrix operator * (const Matrix &rhs) const {
        Matrix ans(n, rhs.m);
        rep (i, 0, n - 1)
            rep (j, 0, rhs.m - 1)
                rep (k, 0, m - 1)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * rhs.a[k][j]) % P;
        return ans;
    }
} f;

Matrix qpow(Matrix x, ll b) {
    Matrix ans(x.n, x.m);
    rep (i, 0, ans.n - 1)
        ans.a[i][i] = 1;
    for (; b; b >>= 1, x = x * x)
        if (b & 1)
            ans = ans * x;
    return ans;
}

int main() {
    freopen("testdata.in", "r", stdin);
    freopen("testdata.ans", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll p, k;
    cin >> p >> k;
    f.n = f.m = p;
    rep (i, 0, p - 1)
        rep (j, 0, p - 1)
            cin >> f.a[i][j];
    f = qpow(f, k);
    rep (i, 0, p - 1) {
        rep (j, 0, p - 1)
            cout << f.a[i][j] << " ";
        cout << endl;
    }
}
