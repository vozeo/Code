#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 1e5 + 5;

template <typename T>
void read(T &x) {
	char c;
    int f = 1;
	while (!isdigit(c = getchar()))
        if (c == '-')
            f = -1;
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
    x *= f;
}

int n, p, ans;
long long a[N], s[N], S, cnt;

int main() {
    /* freopen("bread34.in", "r", stdin); */
    read(n), read(S);
    rep (i, 1, n)
        read(a[i]);
    rep (i, 1, n) {
        cnt += a[i];
        if (cnt > S) cnt -= a[i - ans];
        else {
            p = i, ans++;
            while (cnt + a[i - ans] <= S && i > ans)
                cnt += a[i - ans], ans++;
        }
        /* assert(cnt > 0); */
    }
    if (ans) printf("%d \n%d %d\n", ans, p - ans, n - p);
    else puts("-1\n");
	return 0;
}
