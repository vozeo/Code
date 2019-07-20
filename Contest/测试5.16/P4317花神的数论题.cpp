#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i_, s_, t_) for (ll i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1e5 + 5;

template <typename T>
void read(T &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

ll lgn;

ll sum(ll x) {
    int ans = 0;
    return ans;
}

int main() {
    ll n;
    scanf("%lld", &n);
    lgn = log(n) / log(2) + 1;
    ll ans = 1, j, res;
    const int P = 10000007;
    rep (i, 1, n) {
        j = i, res = 0;
        while (j)
            res += j & 1, j >>= 1;
        ans = ans * res % P;
    }
    printf("%lld\n", ans);
}
