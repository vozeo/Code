#include <cstdio>
#include <cctype>
typedef long long ll;
using namespace std;

int T;
ll l, r, a;

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

ll count(ll n)
{
    ll s = 1;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            int tot = 0;
            while (n % i == 0)
                n /= i, tot++;
            s *= tot + 1;
        }
    }
    if (n > 1)
        s <<= 1;
    return s;
}

int main()
{
    read(T);
    while (T--)
    {
        read(l), read(r), read(a);
        if (r < a)
            printf("-1\n");
        else
        {
            if (l / a == r / a)
                printf("%lld\n", count(l / a * a));
            else
                printf("%lld\n", count(a));
        }
    }
    return 0;
}