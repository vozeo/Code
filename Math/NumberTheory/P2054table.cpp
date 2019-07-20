#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
int a[MAXN], b[MAXN], n, m;
inline void refresh() {
  int *p1 = a + 1, *p2 = a + 1 + (n >> 1), *p = b + 1;
  for (int i = 1; i <= (n >> 1); ++i) *p++ = *p2++, *p++ = *p1++;
}

int main() {
  //cin >> n >> m;
  n = m = 10;
  for(int i = 1; i <= n; ++i) a[i] = i;
  for(int i = 1; i <= m; ++i) {
    refresh();
    for(int i = 1; i <= n; ++i) cout << b[i] << ' ';
    puts("");
    swap(a, b);
  }
  return 0;
}
