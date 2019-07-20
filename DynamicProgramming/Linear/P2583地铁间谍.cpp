#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int n, T, m1, m2, a[255], b[255], t[55], f[205][55], ca;
bool has_train[205][55][2];

void init()
{
	memset(has_train, 0, sizeof(has_train));
	memset(f, 0x3f, sizeof(f));
}

void work()
{
	f[T][n] = 0;
	for (int i = T - 1; i >= 0; --i)
		rep(j, 1, n)
		{
			f[i][j] = f[i + 1][j] + 1;
			if (has_train[i][j][1] && i + t[j] <= T && j < n)
				f[i][j] = std::min(f[i][j], f[i + t[j]][j + 1]);
			if (has_train[i][j][0] && i + t[j - 1] <= T && j > 1)
				f[i][j] = std::min(f[i][j], f[i + t[j - 1]][j - 1]);
		}
	++ca;
	printf("Case Number %d: ", ca);
	if (f[0][1] >= 0x3f3f3f3f)
		printf("impossible\n");
	else
		printf("%d\n", f[0][1]);
}

int main()
{
	while (true)
	{
		init();
		scanf("%d", &n);
		if (n == 0)
			break;
		scanf("%d", &T);
		rep(i, 1, n - 1)
			scanf("%d", &t[i]);
		scanf("%d", &m1);
		rep(i, 1, m1)
		{
			scanf("%d", &a[i]);
			int x = a[i], y = 1;
			while (x <= T && y < n)
			{
				has_train[x][y][1] = true;
				x += t[y], y++;
			}
		}
		scanf("%d", &m2);
		rep(i, 1, m2)
		{
			scanf("%d", &b[i]);
			int x = b[i], y = n;
			while (x <= T && y > 1)
			{
				has_train[x][y][0] = true;
				x += t[y - 1], y--;
			}
		}
		work();
	}
	return 0;
}