#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef long long ll;
char s[60005];
bool As;
int len;
ll ans;

void solve1() {
    for (int i = 4; i <= len; i += 2)
        ans += 1ll * (len - i + 1) * (((i - 4) >> 1) + 1);
}

bool cal(int x, int y, int z) {
    rep (i, 1, z)
        if (s[x + i] != s[y + i])
            return false;
    return true;
}

void solve2() {
    for (int i = 4; i <= len; i += 2)
        rep (j, 0, len - i)
            for (int k = 2; k < i; k += 2)
                if (cal(j, j + (k >> 1), k >> 1) && cal(j + k, j + k + ((i - k) >> 1), (i - k) >> 1))
                    ++ans;
}

int main() {
    freopen("P1117.in", "r", stdin);
    int T;
    scanf("%d\n", &T);
    while (T--) {
        scanf("%s", s + 1);
        len = strlen(s + 1), As = true, ans = 0;
        rep (i, 2, len)
            if (s[i] != s[i - 1])
                As = false;
        if (As) solve1();
        else solve2();
        printf("%lld\n", ans);
    }
}
