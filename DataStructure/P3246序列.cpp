#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
const int N = 1e5 + 5;

ll a[N], fl[N], fr[N], gl[N], gr[N];
int stk[N], pre[N], suc[N], t[N][20], lg[N], pw[20];
int n, m, top;

template<typename T>
void read(T &x) {
    char ch;
    int f = 1;
    while (!isdigit(ch = getchar()))
        if (ch == '-') f = -1;
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
    x *= f;
}

int getmin(int x, int y) {
    return a[x] < a[y] ? x : y;
}

void prework() {
    a[0] = a[n + 1] = INT_MAX;
    rep (i, 1, n) {
        while (a[stk[top]] >= a[i] && top)
            --top;
        pre[i] = stk[top], stk[++top] = i;
    }
    stk[top = 0] = n + 1;
    per (i, n, 1) {
        while (a[stk[top]] >= a[i] && top)
            --top;
        suc[i] = stk[top], stk[++top] = i;
    }
    lg[1] = 0;
    rep (i, 2, n)
        lg[i] = lg[i >> 1] + 1;
    pw[0] = 1;
    rep (i, 1, lg[n])
        pw[i] = pw[i - 1] << 1;
    rep (j, 1, lg[n])
        rep (i, 1, n - pw[j] + 1)
            t[i][j] = getmin(t[i][j - 1], t[i + pw[j - 1]][j - 1]);
    rep (i, 1, n)
        fl[i] = fl[pre[i]] + a[i] * (i - pre[i]), gl[i] = gl[i - 1] + fl[i];
    per (i, n, 1)
        fr[i] = fr[suc[i]] + a[i] * (suc[i] - i), gr[i] = gr[i + 1] + fr[i];
}

int query(int l, int r) {
    int p = lg[r - l + 1];
    return getmin(t[l][p], t[r - pw[p] + 1][p]);
}

int main() {
    freopen("P3246.in", "r", stdin);
    int l, r, p;
    read(n), read(m);
    rep (i, 1, n)
        read(a[i]), t[i][0] = i;
    prework();
    rep (i, 1, m) {
        read(l), read(r), p = query(l, r);
        printf("%lld\n", a[p] * (r - p + 1) * (p - l + 1) + 
                gl[r] - gl[p] - fl[p] * (r - p) +
                gr[l] - gr[p] - fr[p] * (p - l));
    }
}
