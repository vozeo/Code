#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (long long i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (long long i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
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

int res, ansh, anst, n;
long long a[N], s[N], sum, S, mn = INT_MAX;

int main() {
    read(n), read(S);
    rep (i, 1, n)
        read(a[i]), mn = min(mn, a[i]);
    if (mn > S) {
        puts("-1");
        return 0;
    }

    /* rep (i, 1, n) */
    /*     a[i] -= mn; */
    /* S -= (long long)n * mn; */

    int h = 1, t = 1;

    while(h < n) {
        while (t < n && sum <= S)
            sum += a[t++];
        printf("%d %d\n", h, t);
        if (t - h > res) {
            res = t - h;
            ansh = h, anst = t;
        }
        sum -= a[h++];
    }
    /* rep (i, 1, n) */
    /*     rep (j, i, n) */
    /*         if (s[j] - s[i - 1] <= S) */
    /*             if (j - i + 1 > res) { */
    /*                 res = j - i + 1; */
    /*                 anss = i, anst = j; */
    /*             } */
    /* while (true) { */
    /*     printf("%d %d %lld\n", s, t, sum); */
    /*     while (t <= n && sum > S) */
    /*         sum -= a[++t]; */
    /*     if (sum > S) break; */
    /*     if (t - s > res) { */
    /*         res = t - s; */
    /*         anss = s, anst = t; */
    /*     } */
    /*     sum += a[++s]; */
    /* } */
    printf("%d \n%d %d\n", res, ansh - 1, n - anst);
	return 0;
}
