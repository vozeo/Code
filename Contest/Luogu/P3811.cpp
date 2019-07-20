#include <bits/stdc++.h>

//线性
/*
int n, p, inv[3000010];
int main()
{
	scanf("%d%d", &n, &p);
	inv[1] = 1;
	printf("1\n");
	for (int i = 2; i <= n; ++i)
	{
		inv[i] = (long long)inv[p % i] * (p - p / i) % p;
		printf("%d\n", inv[i]);
	}
	return 0;
}
*/
inline void exgcd(int a, int b, int &x, int &y)// exgcd，复杂度O(nlogn)，也能过。
{
	if (!b)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}

int main()
{
	int n, p, x, y;
	scanf("%d%d", &n, &p);
	printf("1\n");
	for (int i = 2; i <= n; ++i)
	{
		exgcd(i, p, x, y);
		printf("%d\n", (x % p + p) % p);
	}
	return 0;
}