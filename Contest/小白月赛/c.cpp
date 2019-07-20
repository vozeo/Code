#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1005, P = 1e9 + 7;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int a, h[N];
bool b[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n)
        read(h[i]);
    while (m--) {
        read(a);
        rep (i, 1, n)
            b[i] = (a >= h[i]);
        int ans = 0, i = 0;
        while (i < n) {
            while (b[i + 1]) ++i;
            ++ans;
            while (!b[i + 1]) ++i;
        }
        printf("%d\n", ans);
    }
}
