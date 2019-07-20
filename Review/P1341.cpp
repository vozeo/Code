#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 150;
int n, d[N], g[N][N];
bool vis[N][N];

void print(int x) {
    cout << (char)x;
    rep (i, 1, 128)
        if (g[x][i] && !vis[x][i])
            vis[x][i] = vis[i][x] = true, print(i);
}

int main() {
    char s[5];
    ios::sync_with_stdio(false);
    cin >> n;
    rep (i, 1, n) {
        cin >> s;
        if (s[0] != s[1])
            ++d[s[0]], ++d[s[1]];
        g[s[0]][s[1]] = g[s[1]][s[0]] = 1;
    }
    /* rep (i, 1, 128) */
    /*     if (d[i]) */
    /*         cout << i << " " << d[i] << endl; */
    int cnt = 0;
    rep (i, 1, 128) {
        if (d[i] > 2) {
            cout << "No Solution" << endl;
            return 0;
        }
        if (d[i] == 1)
            ++cnt;
    }
    if (cnt > 2) {
        cout << "No Solution" << endl;
        return 0;
    }
    if (cnt == 2) {
        rep (i, 1, 128)
            if (d[i] == 1) {
                print(i);
                break;
            }
    } else {
        rep (i, 1, 128)
            if (d[i]) {
                print(i);
                break;
            }
    }
    cout << endl;
    /* rep (i, 1, 128) */
    /*     rep (j, 1, 128) */
    /*         if (g[i][j]) */
    /*             cout << (char)i << char(j) << endl; */
}
