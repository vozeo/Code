#include <bits/stdc++.h>
using namespace std;

char s[5][10] = {"2(0)", "2", "2(2)"};

void work(int x) {
	while (x) {
		int cur = 1, a = 0;
		while (cur <= x)
			cur <<= 1, a++;
		cur >>= 1, a--;
		if (a > 2) {
			printf("2(");
			work(a);
			printf(")");
		} else
			printf("%s", s[a]);
		x -= cur;
		if (x)
			printf("+");
	}
}

int main() {
	int n;
	scanf("%d", &n);
	work(n);
	return 0;
}
