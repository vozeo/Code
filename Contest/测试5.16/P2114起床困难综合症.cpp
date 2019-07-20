#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 5;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int n, m, t[N], op[N];

int atk(int x, int s) {
    int p;
    rep (j, 1, n) {
        p = (t[j] >> s) & 1;
        if (op[j] == 1)
            x &= p;
        else if (op[j] == 2)
            x |= p;
        else if (op[j] == 3)
            x ^= p;
    }
    return x << s;
}

int main() {
    freopen("P2114.in", "r", stdin);
    char s[10];
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%s%d", s, &t[i]);
        if (s[0] == 'A')
            op[i] = 1;
        else if (s[0] == 'O')
            op[i] = 2;
        else if (s[0] == 'X')
            op[i] = 3;
    }
    int tot = 1, lim = 0, sum = 0, p1, p0, ans = 0;
    while (tot <= m)
        ++lim, tot <<= 1;
    --lim;
    lim = 30;
    /*
    if (!m) {
        printf("%d\n", atk(0, 0));
        return 0;
    }
    */
    per (i, lim, 0) {
        p1 = atk(1, i);
        p0 = atk(0, i);
        if (p1 > p0 && sum + (1 << i) <= m)
            ans += p1, sum += (1 << i);
        else ans += p0;
    }
    printf("%d\n", ans);
}
