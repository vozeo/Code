#include <bits/stdc++.h>
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;
using namespace std;

int n, m, op, l, r, x, y, cnt, last, a[100005];

void read(int &xx) {
	char c;
	while (!isdigit(c = getchar()));
	for (xx = c - '0'; isdigit(c = getchar()); xx = xx * 10 + c - '0');
}

int main() {
	read(n), read(m);
	rep (i, 1, n)
		read(a[i]);
	rep (i, 1, m) {
		read(op);
		if (op == 1)
			read(x), read(y), a[x] = y;
		else {
			read(l), read(r), read(x), read(y);
			cnt = last = 0;
			rep (j, l, r)
				if (a[j] != last) {
					if (a[j] >= x && a[j] <= y)
						cnt++;
					last = a[j];			
				}
			printf("%d\n", cnt);
		}
	}
	return 0;
}
