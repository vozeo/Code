#include <bits/stdc++.h>
using namespace std;
#define M 600000 + 10

int t, n, ans, sum, num;
int a[M], b[M];

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		ans = 0;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		while (next_permutation(a + 1, a + n + 1))
		{
			num = 0, sum = 0;
			for (int i = 1; i <= n; i++)
			{
				b[i] = a[i];
				num += abs(i - a[i]);
			}
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n - 1; j++)
					if (b[j] > b[j + 1])
					{
						swap(b[j], b[j + 1]);
						sum++;
					}
			if (sum * 2 == num)
				ans++;
		}
		printf("%d\n", ans % 998244353);
	}
	return 0;
}