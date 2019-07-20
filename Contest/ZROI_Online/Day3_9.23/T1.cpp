#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);i_++)
int n, m, mx, a[1005][1005];

int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if(c == '-')
			f = -1;
		c = getchar();
	}
	while (isdigit(c))
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

int max(int x, int y)
{
	return x > y ? x : y;
}

int main()
{
	scanf("%d%d", &n, &m);
	rep (i, 1, n)
		rep (j, 1, m)
			a[i][j] = read();
	rep (i, 1, n)
		rep (j, 1, m)
			rep (k, 1, n)
				rep (l, 1, m)
				{
					bool flag = true;
					rep (r, i, k)
						rep(c, j, l)
							if (a[i][j] + a[r][c] > a[i][c] + a[r][j])
							{
								flag = false;
								break;
							}
					if (flag)
						mx = max(mx, (k - i + 1) * (l - j + 1));
				}
	printf("%d", mx);
	return 0;
}
