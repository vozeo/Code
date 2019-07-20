#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
const int N = 5e5 + 5, M = 1005;
ll a[N], s[N], t[M * M], ans;
int cnt;

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

template<typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getc()));
    for (x = ch - '0'; isdigit(ch = getc()); x = x * 10 + ch - '0');
}

int main() {
    int n, p;
    read(n), read(p);
    rep (i, 1, n)
        read(a[i]), s[i] = s[i - 1] ^ a[i];
    rep (i, 1, n)
        rep (j, i, n)
            t[++cnt] = s[j] ^ s[i - 1];
    sort(t + 1, t + cnt + 1);
    rep (i, cnt - p + 1, cnt)
        ans += t[i];
    cout << ans << endl;
}
