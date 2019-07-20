#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define N 1000005
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
int n, m, r[N], d[N], s[N], t[N];
vector<int> es[N];

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

int main()
{
    read(n);
    read(m);
    rep(i, 1, n)
        read(r[i]);
    rep(i, 1, m)
        read(d[i]), read(s[i]), read(t[i]);
    rep(i, 1, m)
    {
        es[s[i]].push_back(d[i]);
        es[t[i] + 1].push_back(-d[i]);
    }
    int sum = 0, cur = m;
    rep(i, 1, n)
    {
        for (int j = 0; j < (int)es[i].size(); ++j)
            sum += es[i][j];
        for (; sum > r[i]; --cur)
            if (s[cur] <= i && t[cur] >= i)
                sum -= d[cur];
    }
    if (cur == m)
        printf("0\n");
    else
        printf("-1\n%d\n", cur + 1);
    return 0;
}