#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;

int a[100] = {0, 9, -31, -42, -54, -64, -70, -76, -81};
map<string, int> m;

void print(int x) {
	if (x == 1)
		printf("+9 to -31\n");
	else
		printf("%d to %d\n", a[x], a[x + 1]);
}
int main() {
	int n;
	string s;
	m["OW"] = 1, m["DG"] = 2;
	m["MG"] = 3, m["LG"] = 4, m["B"] = 5, m["W"] = 6, m["CMG"] = 7;
	scanf("%d", &n);
	rep (i, 1, n) {
		cin >> s;
		if (s == "WMG")
			printf(">+9\n");
		else if (s == "CDG")
			printf("<=-81\n");
		else
			print(m[s]);
	}
}









