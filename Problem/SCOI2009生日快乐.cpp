#include<bits/stdc++.h>
using namespace std;

double dfs(double x, double y, int num)
{
	if (x > y)
		swap(x, y);
	if (num == 1)
		return y / x;
	double ans = 2e9, t1 = 0, t2 = 0;
	for (int i = 1; i <= num / 2; ++i)
	{
		t1 = max(dfs(x, y * i / num, i), dfs(x, y * (num - i) / num, num - i));
		t2 = max(dfs(y, x * i / num, i), dfs(y, x * (num - i) / num, num - i));
		ans = min(ans, min(t1, t2));
	}
	return ans;
}

int main()
{
	double a, b;
	int n;
	scanf("%lf%lf%d", &a, &b, &n);
	printf("%.6f", dfs(a, b, n));
	return 0;
}
