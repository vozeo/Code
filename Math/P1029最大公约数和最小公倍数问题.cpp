#include <bits/stdc++.h>
using namespace std;

int x, y, z, ans = 1, a[10005], b[10005];

int main() {
	scanf("%d%d", &x, &y);
	z = max(x, y);
	for (int i = 2; i * i <= z; ++i) {
		while (x % i == 0)
			x /= i, a[i]++;
		while (y % i == 0)
			y /= i, b[i]++;
	}
	for (int i = 2; i * i <= z; ++i) {
		if (a[i] > b[i]) {
			printf("0\n");
			return 0;
		}
		if (a[i] < b[i])
			ans <<= 1;	
	}
	if (x > 1 && y > 1 && x != y) {
		printf("0\n");
		return 0;
	}
	if (x == 1 && y > 1)
		ans <<= 1;
	printf("%d\n", ans);
	return 0;
}
