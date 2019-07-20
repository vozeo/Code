#include <bits/stdc++.h>
using namespace std;

int main() {
	scanf("%d", &n);
	rep (i, 1, n)
		scanf("%d", a + i);
	per (i, n, 1) {
		if (vis[i])
			continue;
		per (j, i - 1, 1) {
			if (vis[i])
				continue;
			if (a[i] == lst - 1)
				vis[i] == true, lst = a[i], tp[++cnt] = a[i];


		}
}
