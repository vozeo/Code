#include <bits/stdc++.h>
using namespace std;

struct plan {
	int l, r;
	plan() {}
	plan(const int x, const int y) : l(x), r(y) {}
	bool operator<(const plan &rhs) const {
		return r < rhs.l;
	}
};

set<plan> q;
int main() {
	int n, cnt, x, y;
	string s;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		if (s == "A") {
			cnt = 0;
			scanf("%d%d", &x, &y);
			plan t = plan(x, y);
			set<plan>::iterator it;
			while ((it = q.find(t)) != q.end())
				cnt++, q.erase(it);
			q.insert(t);
			printf("%d\n", cnt);
		} else
			printf("%d\n", (int)q.size());
	}
	return 0;
}
