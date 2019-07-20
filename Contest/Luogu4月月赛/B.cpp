#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 15;
typedef unsigned long long ull;
int n, k, f[N];
ull a[N], b[N], an[N], bn[N], r[N], d[N];
bool vis[N], has_ans;

ull gcd(ull x, ull y) {
    return y ? gcd(y, x % y) : x;
}

ull lcm(ull x, ull y) {
    return x / gcd(x, y) * y;
}

bool judge() {
    ull mul = 1;
    rep (i, 1, n) {
        d[i] = a[i] * b[f[i]];
        mul *= d[i];
    }
    mul = sqrt(mul);
    rep (i, 1, k)
        r[i] = mul / d[i];
    int tot = 0;
    rep (i, 1, k - 1)
        rep (j, i + 1, k) {
            an[++tot] = gcd(r[i], r[j]);
            bn[tot] = lcm(r[i], r[j]);
        }
    sort(an + 1, an + n + 1);
    sort(bn + 1, bn + n + 1);
    /* rep (i, 1, n) */
    /*     printf("%lld ", an[i]); */
    /* puts(""); */
    rep(i, 1, n) {
        if (a[i] != an[i] || b[i] != bn[i])
            return false;
    }
    return true;
}

void dfs() {
    do {
        if (judge()) {
            rep (i, 1, k)
                printf("%lld ", r[i]);
            puts("");
            has_ans = true;
            return;
        }
    } while (next_permutation(f + 1, f + n + 1));
}

int main() {
    int T;
    scanf("%d%d", &T, &k);
    n = k * (k - 1) / 2;
    while (T--) {
        has_ans = false;
        rep (i, 1, n)
            scanf("%lld", &a[i]);
        rep (i, 1, n)
            scanf("%lld", &b[i]);
        if (k == 2) {
            printf("%lld %lld\n", a[1], b[1]);
            continue;
        }
        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        rep (i, 1, n)
            f[i] = i;
        dfs();
    }
}
