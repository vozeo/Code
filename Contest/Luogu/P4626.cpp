#include <bits/stdc++.h>
#define MOD 100000007
typedef long long ll;

bool vis[100000005];
int cnt, ans, pri[5762000];

void work(int n)
{
	cnt = 0, ans = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])
		{
			ll x = i, y = (ll)i * i;
			pri[++cnt] = i;
			while (y <= n)
				x = y, y *= i;
			ans = x * ans % MOD;
		}
		ll t;
		for (int j = 1; j <= cnt && (t = (ll)i * pri[j]) <= n; j++)
		{
			vis[t] = true;
			if (i % pri[j] == 0)
				break;
		}
	}
	printf("%d", ans);
}

int main()
{
	int n;
	scanf("%d", &n);
	work(n);
	return 0;
}
