#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 105;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int n, m, res, ans, t, h, tp;
char a[105][3 * 105 * 105];



int main() {
    freopen("a4.in", "r", stdin);
    freopen("a4.out", "w", stdout);
    read(n), read(m);
    rep (i, 1, n) {
        scanf("%s", s[i]);
        len[i] = strlen(s[i]);
        re (j, 0, len[i])
            qz[i][j] = qz[i][j - 1] + (s[i][j] == '0');
        qsu[i] = qz[i][len[i] - 1];

    }
        
    rep (i, 1, m) {
        read(mk[i]);
        rep (j, 1, mk[i])
            scanf("%d", &x), sa[i].push_back(x);
        re (j, 0, (int)sa[i].size())
            qz[i + n][j] = qz[i + n][j - 1] + qsu[sa[i][j]];
        qsu[i + n] = qz[i + n][sa[i].size() - 1];
    }

    read(Q);
    rep (i, 1, Q) {
        read(ax), read(al), read(ar);
        printf("%lld", query(ax, r) - query(ax, l - 1));
    }

}
