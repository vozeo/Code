#include <iostream>
#include <vector>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_) 
using namespace std;

int k, n, m, f[305][305], s[305];
vector<int> son[305];

template<typename T>
void read(T &xx)
{
	char cc;
	while (!isdigit(cc = getchar()));
	for (xx = cc - '0'; isdigit(cc = getchar()); xx = xx * 10 + cc - '0');
}

void dp(int x)
{
	for (int i = 0; i < (int)son[x].size(); ++i)
	{
		int y = son[x][i];
		dp(y);
		for (int t = m; t >= 0; --t)
			for (int j = t; j >= 0; --j)
				f[x][t] = max(f[x][t], f[x][t - j] + f[y][j]);	
	}
	if (x)
		for (int t = m; t > 0; --t)
			f[x][t] = f[x][t - 1] + s[x];
}

int main()
{
	scanf("%d%d", &n, &m);
	rep (i, 1, n)
	{
		read(k), read(s[i]);
		son[k].push_back(i);
	}
	dp(0);
	printf("%d\n", f[0][m]);
	return 0;
}
