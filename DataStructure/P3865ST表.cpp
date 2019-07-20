#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int t[N][18], lg[N];

int query(int l, int r) {
    int g = lg[r - l + 1];
    return max(t[l][g], t[r - (1 << g) + 1][g]);
}

int main() {
    freopen("P3865.in", "r", stdin);
    int n, m, l, r;
    read(n), read(m);
    lg[0] = -1;
    rep (i, 1, n)
        read(t[i][0]), lg[i] = lg[i >> 1] + 1;
    rep (j, 1, lg[n])
        rep (i, 1, n - (1 << j) + 1)
            t[i][j] = max(t[i][j - 1], t[i + (1 << (j - 1))][j - 1]);
    rep (i, 1, m)
        read(l), read(r), printf("%d\n", query(l, r));
}
