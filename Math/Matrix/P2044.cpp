#include <bits/stdc++.h>
using namespace std;
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

typedef long long ll;
ll P;

ll mul(ll x, ll b) {
    ll ans = 0;
    for (; b; b >>= 1, x = x * 2 % P)
        if (b & 1)
            ans = (ans + x) % P;
    return ans;
}

struct Matrix {
    ll a[2][2];
    Matrix() {
        a[0][0] = a[1][0] = a[0][1] = a[1][1] = 0;
    }
    Matrix operator * (const Matrix &b) const {
        Matrix ans;
        re (i, 0, 2)
            re (j, 0, 2)
                re (k, 0, 2)
                    ans.a[i][j] = (ans.a[i][j] + mul(a[i][k], b.a[k][j])) % P;
        return ans;
    }
} f, g;


Matrix qpow(Matrix x, ll b) {
    Matrix ans;
    ans.a[0][0] = ans.a[1][1] = 1;
    for (; b; b >>= 1, x = x * x)
        if (b & 1)
            ans = ans * x;
    return ans;
}

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    ll n, G;
    read(P), read(g.a[0][0]), read(f.a[0][1]), read(f.a[0][0]), read(n), read(G);
    g.a[0][0] %= P, f.a[0][1] %= P, f.a[0][0] %= P;
    g.a[1][0] = g.a[1][1] = 1;
    cout << (f * qpow(g, n)).a[0][0] % G << endl;
}

