#include <cstdio>
#include <iostream>
#include <cctype>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for(int i_ = (s_); i_ < (t_); ++i_)
using namespace std;

int cur; 
char s[105];

template<typename T>
inline void read(T &x)
{
	char c;
	while (!isdigit(c = getchar()));
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

void print(int x)
{
	if (x == 1)
		printf("Yes\n");
	else if (x == -1)
		printf("ERR\n");
	else if (x == 0)
		printf("No\n");
}

int work()
{
	cur = 1;
	int l, n, pow_cnt = 0, pow_mx = 0;
	bool dont_cnt = false;
	char o;
	scanf("%d", &l);
	scanf("O(%c", &o);
	if (o == 'n')
		scanf("^%d", &n);
	scanf(")");
	
	while(l--)
	{
		char f, r;
		string x, y;
		scanf("%c", &f);
		if (f == 'F')
		{
			scanf("%c", &r);
			rep (i, 1, cur - 1)
				if (s[i] == r)
					return -1;
			s[cur++] = r;
			cin >> x >> y;
			if (x == "n" && y != "n")
				dont_cnt = true;
			else if (x != "n" && y == "n")
			{
				if (!dont_cnt)
					pow_cnt++;
			}
			else
			{
				int a = 0, b = 0;
				//int len_x = , len_y = strlen(y);
				re(i, 0, (int)x.length())
					a = a * 10 + x[i] - '0';
				re(i, 0, (int)y.length())
					b = b * 10 + y[i] - '0';
				if (a > b)
					dont_cnt = true;
			}
		}
		else if (f == 'E')
		{
			cur--;
			pow_mx = max(pow_mx, pow_cnt);
			pow_cnt--;
			if (cur == 0)
				return -1;
		}
	}
		if (cur > 1)
			return -1;
		if (pow_mx == pow_cnt)
			return 1;
		else
			return 0;
}

int main()
{
	freopen("complexity.in", "r", stdin);
	//freopen("complexity.out", "w", stdout);
	int N;
	scanf("%d", &N);
	while(N--)
	{
		print(work());
	}
	fclose(stdout);
	return 0;
}
