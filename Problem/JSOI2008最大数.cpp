/*******************************************************************************
 * Author		: Vozeo
 * Last modified: 2018-12-18 23:38
 * Filename		: P1198.cpp
 * Description	: 
*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;
#define N 200005

char c;
int M, n, tail, q[200005], pos;
long long p, D, s[200005], t;

int main() {
	scanf("%d%lld", &M, &D);
	for (int i = 1; i <= M; ++i) {
		c = 0;
		while(c != 'A' && c != 'Q')
			c = getchar();
		scanf("%lld", &p);
		if (c == 'A') {
			n++;
			p = ((p + t) % D + D) % D;
			while (tail > 0 && s[tail - 1] < p)
				tail--;
			s[tail] = p, q[tail++] = n;
		} else {
			pos = lower_bound(q, q + tail, n - p + 1) - q;
			printf("%lld\n", t = s[pos]);
		}
	}
	return 0;
}
