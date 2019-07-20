#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = (s); i <= (t); ++i)
const int N = 3e5 + 5;

void read(int &x) {
	char c;
	while (!isdigit(c = getchar()));
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

vector<int> s[N];
int a[N];

int main() {
	freopen("P3939.in", "r", stdin);
	int n, m, x, l, r, op;
	read(n), read(m);
	rep (i, 1, n) {
		read(a[i]);
		s[a[i]].push_back(i);
	}
	rep (i, 1, m) {
		read(op);
		if (op == 1) {
			read(l), read(r), read(x);
			printf("%ld\n", upper_bound(s[x].begin(), s[x].end(), r) - lower_bound(s[x].begin(), s[x].end(), l));
		} else {
			read(x);
			(*lower_bound(s[a[x]].begin(), s[a[x]].end(), x))++, (*lower_bound(s[a[x + 1]].begin(), s[a[x + 1]].end(), x + 1))--;
			swap(a[x], a[x + 1]);
		}
	}
} 
