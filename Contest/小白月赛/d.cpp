#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 2e6 + 5, P = 1e9 + 7;
typedef long long ll;

template <typename T>
void read(T &x) {
    char ch;
    int f = 1;
    while (!isdigit(ch = getchar()))
        if (ch == '-')
            f = -1;
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
    x *= f;
}

int a[N], s[N], stk[N], id[N];

int main() {
    freopen("d.in", "r", stdin);
    int n;
    read(n);
    rep (i, 1, n)
        read(a[i]), s[i] = s[i - 1] + a[i];
    int ans = 0, top = 0;
    stk[0] = INT_MIN;
    per (i, n, 1) {
        if (s[i] > stk[top]) stk[++top] = s[i], id[top] = i;
        int p = upper_bound(stk + 1, stk + top + 1, s[i - 1]) - stk;
        if (stk[p] > s[i - 1])
            ans = max(ans, id[p] - i + 1);
    }
    printf("%d\n", ans);
}
