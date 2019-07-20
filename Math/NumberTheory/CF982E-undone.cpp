#include <bits/stdc++.h>

inline int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return d;
}

int main()
{
	int n, m, a, b, x, y, vx, vy, d;
	scanf("%d%d%d%d%d%d", &n, &m, &a, &b, &vx, &vy);
	if (vx == 0)
	{
		if (a == n)
		{
			if (vy == 1)
				printf("%d %d", n, m);
			else if (vy == -1)
				printf("%d 0", n);
		}
		else if (a == 0)
		{
			if (vy == 1)
				printf("0 %d", m);
			else if (vy == -1)
				printf("0 0");
		}
		else
			printf("-1");
		return 0;
	}
	if (vy == 0)
	{
		if (b == m)
		{
			if (vx == 1)
				printf("%d %d", n, m);
			else if (vx == -1)
				printf("0 %d", m);
		}
		else if (b == 0)
		{
			if (vx == 1)
				printf("%d 0", n);
			else if (vx == -1)
				printf("0 0");
		}
		else
			printf("-1");
		return 0;
	}

	d = exgcd(m, n, x, y);
	if (d % (a - b));
}
