#include <bits/stdc++.h>

inline void exgcd(int a, int b, int &x, int &y)
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
	int a, b, x, y;
	scanf("%d%d", &a, &b);
	exgcd(a, b, x, y);
	printf("%d", (x % b + b) % b);
	return 0;
}