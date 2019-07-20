#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

typedef long long ll;
const int P = 1e9 + 7;

struct Matrix {
    ll a[26][26];
    Matrix() {
        memset(a, 0, sizeof a);
    }
    Matrix operator * (const Matrix &b) const {
        Matrix ans;
        re (i, 0, 26)
            re (j, 0, 26)
                re (k, 0, 26)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j]) % P;
        return ans;
    }
};

Matrix qpow(Matrix x, ll p) {
    Matrix ans;
    re (i, 0, 26)
        ans.a[i][i] = 1;
    for (; p; p >>= 1, x = x * x)
        if (p & 1)
            ans = ans * x;
    return ans;
}

char s[100005];

int main() {
    ll n;
    scanf("%lld%s", &n, s);
    int ns = strlen(s);
    Matrix f, g;
    re (i, 0, 26)
        re (j, 0, 26)
            g.a[i][j] = 1;
    re (i, 0, ns)
        g.a[s[i + 1] - 'a'][s[i] - 'a'] = 0;
    re (i, 0, 26)
        f.a[0][i] = 1;
    ll ans = 0;
    f = f * qpow(g, n - 1);
    re (i, 0, 26)
        ans = (ans + f.a[0][i]) % P;
    printf("%lld\n", ans);
}
