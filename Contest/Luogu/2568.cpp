#include <bits/stdc++.h>
typedef long long ll;
int cnt, pri[1000005];
bool vis[10000005];

void prime(int n)
{
	cnt = 0;
	for (int i = 2; i <= n; i++)
	{
		if (!vis[i])
			pri[++cnt] = i;
		ll t;
		for (int j = 1; j <= cnt && (t = pri[j] * i) <= n; j++)
		{
			vis[t] = true;
			if(i % pri[j] == 0)break;
		}
	}
}

void work(int n)
{
	ll ans = 0;
	prime(n);
	for(int i = 1; i <= cnt; i++)
		ans += (n / pri[i]) * 2 - 1;
	printf("%lld", ans);
}

int main()
{
	int n;
	scanf("%d", &n);
	work(n);
	return 0;
}