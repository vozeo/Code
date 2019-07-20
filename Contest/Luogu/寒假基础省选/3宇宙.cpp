#include <bits/stdc++.h>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;
using namespace std;

cint N = 1000005;
int Q, cnt, t, l, r, j, p[N];
short a[N], b[N];
char c;

void work() {
	cnt = t = 0;
	while (!isdigit(c = getchar()));
	for (b[++t] = c - '0'; isdigit(c = getchar()); b[++t] = c - '0');
	scanf("%d%d", &l, &r);
	j = 0;
    rep (i, 2, t) {
       while (j && b[i] != b[j + 1])
		   j = p[j];
       if (b[j + 1] == b[i])
		   j++;
	   p[i] = j;
	}
    j = 0;
    rep (i, l, r) {
		while (j && b[j + 1] != a[i])
			j = p[j];
		if (b[j + 1] == a[i])
			j++;
		if (j == t)
			cnt++, j = p[j];
    }
	printf("%d\n", cnt);
}

int main() {
	scanf("%d", &Q);
	rep (i, 0, 500000)
		a[i * 2] = a[i], a[2 * i + 1] = a[i] ^ 1;
	rep (i, 0, 20)
		cout << a[i];
	cout << endl;
	while (Q--)
		work();
	return 0;
}
