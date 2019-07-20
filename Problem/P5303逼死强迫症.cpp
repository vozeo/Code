#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 2e9, P = 1e9 + 7;
typedef long long ll;

struct Matrix {
    ll a[5][5];
    Matrix() { memset(a, 0, sizeof a); }
    Matrix operator * (const Matrix &rhs) {
        Matrix ans;
        re (i, 0, 5)
            re (j, 0, 5)
                re (k, 0, 5)
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * rhs.a[k][j]) % P;
        return ans;
    }
};

Matrix qpow(Matrix x, int b) {
    Matrix ans;
    re (i, 0, 5)
        ans.a[i][i] = 1;
    for (; b; b >>= 1, x = x * x)
        if (b & 1)
            ans = ans * x;
    return ans;
}

void work() {
    int n;
    cin >> n;
    if (n < 3) {
        puts("0");
        return;
    }
    Matrix f, b;
    f.a[0][2] = f.a[0][3] = f.a[0][4] = 1;
    re (i, 0, 4) b.a[i][0] = 1;
    re (i, 2, 5) b.a[i][2] = 1;
    b.a[0][1] = b.a[2][3] = b.a[4][4] = 1;
    cout << (f * qpow(b, n - 2)).a[0][0] << endl;
}

int main () {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        work();
    }
}
