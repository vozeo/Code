#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

vector<int> a;
char c;
int k, n, mn, cur = 0, sum = 0;

int main()
{
    freopen("cn.in", "r", stdin);
    freopen("cn.out", "w", stdout);
    scanf("%d%d", &n, &mn);
    while (n--)
    {
        while (!isalpha(c = getchar()));
        scanf("%d", &k);
        if (c == 'I')
        {
            if (k >= mn)
                a.insert(upper_bound(a.begin(), a.end(), k), k);
        }
        else if (c == 'A')
            for (int i = 0; i < (int)a.size(); ++i)
                a[i] += k;
        else if (c == 'S')
        {
            for (int i = 0; i < (int)a.size(); ++i)
                a[i] -= k;
            for (int i = 0; i <= (int)a.size(); ++i)
                if (a[i] >= mn || i == a.size())
                {
                    a.erase(a.begin(), a.begin() + i);
                    sum += i;
                    break;
                }
        }
        else
        {
            if (k > (int)a.size())
                printf("-1\n");
            else
                printf("%d\n", *(a.end() - k));
        }
        //printf("Case%d:", n);
        /*
        if (flag == -28)
        {
            printf("NOW:");
            printf("k = %d, size = %d", k, (int)a.size());

            for (int i = 0; i < (int)a.size(); ++i)
                printf("%d ", a[i]);
            printf("\n");
        }
        /*
        printf("NOW:");
        for (int i = 0; i < (int)a.size(); ++i)
            printf("%d ", a[i]);
        printf("\n");
        
        if(c == 'S' && k == 74)
        {
            printf("NOW:");
        for (int i = 0; i < (int)a.size(); ++i)
            printf("%d ", a[i]);
        printf("\n");
        }
        */
    }
    printf("%d\n", sum);
    return 0;
}