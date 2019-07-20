#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
using namespace std;
int main()
{
    /*
    int a[15], n, m;
    scanf("%d%d", &n, &m);
    rep(i, 1, n)
        a[i] = i;
    do
    {
        int sum = 0;
        //rep (i, 1, n)
        //   printf("%d", a[i]);
        //putchar('\n');
        rep (i, 1, n - 1)
            rep (j, i + 1, n)
                if (a[i] > a[j])
                    sum++;
        //printf("%d ", sum);
        if (m == sum)
        {
           rep (i, 1, n)
           printf("%d ", a[i]);
           putchar('\n');
           return 0;
        }

    } while(next_permutation(a + 1, a + n + 1));

    int ms = (1 << 6) - 1;
    rep (i, 0, ms)
    {
        rep (j, 0, 5)
            if ((1 << j) & i)
                printf("%d", j + 1);
        putchar('\n');
    }

    int S = (1 << 5) + (1 << 4) + (1 << 2) + 1;
    for (int i = S; i; i = (i - 1) & S)
    {
        for (int j = 5; j >= 0; j--)
                printf("%d", ((1 << j) & i) > 0);
        putchar('\n');
    }
*/
    int a[10] = {2, 2, 3, 2, 4, 2, 5, 6, 6, 1};
    //unique(a, a + 9);
    sort(a, a + 10);
    cout << unique(a, a + 9) - a << endl;
    rep(i, 0, 9)
            cout << a[i];
        
}