#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 1e5 + 5;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int qz[21][N];
string s[21];

int main() {
    ios::sync_with_stdio(false);
    freopen("t2.in", "r", stdin);
    /* freopen("a4.out", "w", stdout); */
    int n, m, Q, p, ql, qr, len;
    cin >> n >> m;
    rep (i, 1, n)
        cin >> s[i];
    rep (i, 1, m) {
        cin >> ql;
        rep (j, 1, ql)
            cin >> qr, s[i + n] = s[i + n] + s[qr];
    }
    rep (i, 1, n + m) {
        qz[i][0] = (s[i][0] == '1');
        len = s[i].length();
        rep (j, 1, len - 1)
            qz[i][j] = qz[i][j - 1] + (s[i][j] == '1');
    }
    cin >> Q;
    rep (i, 1, Q) {
        cin >> p >> ql >> qr;
        cout << qz[p][qr - 1] - qz[p][ql - 2] << endl;
    }
}
