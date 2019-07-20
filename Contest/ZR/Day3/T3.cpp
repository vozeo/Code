#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;
#define N 500005

int T, n, a[N], b[N], c[N];

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

int main()
{
    while (~scanf("%d", &n))
    {
        rep(i, 1, n)
            read(a[i]);
        rep(i, 1, n)
            read(b[i]);
        bool flag = true;
        rep(i, 1, n)
        {
            int t = a[i];
            while (t != b[i])
            {
                t = a[t];
                if (t == a[i])
                {
                    flag = false;
                    break;
                }
            }
            if (flag == false)
                break;
        }
        if (flag == true)
            printf("Yes\n");
        else
            printf("No\n"); 
    }
    return 0;
}