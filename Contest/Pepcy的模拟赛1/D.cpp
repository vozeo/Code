#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

typedef long long ll;
const int N = 3e6 + 5;

template <typename T>
void read(T &x) {
	char c;
	while (!isdigit(c = getchar()));
	for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0');
}

struct Edge *head[N];
struct Edge {
    int v;
    Edge *nxt;
    Edge() {}
    Edge(int x, int y) : v(y), nxt(head[x]) { head[x] = this; }
} epool[N], *ecur = epool;

int main() {
    srand(19260817);
	int n, m;
	scanf("%d %d", &n, &m);
    /* printf("%d", rand() % 500); */
    if (m > 100)
        puts("Yes");
    else puts("No");
	return 0;
}
