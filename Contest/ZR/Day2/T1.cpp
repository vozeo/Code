#include <bits/stdc++.h>
typedef long long ll;
ll T, L, R, A;

template <typename T>
inline void read(T &x)
{
    char c;
    while (!isdigit(c = getchar()));
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

int main()
{
    //scanf("%lld", &T);
    read(T);
    while (T--)
    {
        read(L), read(R), read(A);
        //scanf("%lld%lld%lld", &L, &R, &A);
        //printf("%lld %lld %lld\n", L, R, A);
        L /= A, R /= A;
        if (L == R)
            A *= L;
        if (!A)
        {
            printf("-1\n");
            continue;
        }
        ll sum = 1;
        for (int i = 2; i * i <= A; i++)
        {
            if (A % i != 0)
                continue;
            int c = 0;
            while (A % i == 0)
                A /= i, ++c;
            sum *= c + 1;
        }
        if (A > 1)
            sum *= 2;
        printf("%lld\n", sum);
    }
    return 0;
}