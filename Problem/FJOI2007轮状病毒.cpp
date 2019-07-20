#include <bits/stdc++.h>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)

long long c[205][205];
int n, m;

int main()
{
	rep (i, 1, 200)
		c[i][1] = i, c[i][i] = 1, c[i][0] = 1;
	rep (i, 2, 200)
		rep (j, 2, i)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	scanf("%d", &n);
	//printf("%lld", c[n][m]);
	if (n == 1)
		printf("1\n");
	else if (n == 2)
		printf("1\n");
	else
		printf("%lld\n", c[2 * n][n] - n * c[2 * n - 3][n - 3] - 1 - n * n);
	return 0;
}

