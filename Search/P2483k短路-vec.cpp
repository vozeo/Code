#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

typedef unsigned int uint;
const int N = 5e3 + 5, M = 2e5 + 5;

double d[N], W;
int n, m, cnt[N];
bool vis[N];
vector<pair<int, double> > e[N], fe[N];
priority_queue<pair<double, int> > q;

void dij() {
    fill(d + 1, d + n + 1, INT_MAX);
    d[n] = 0;
    q.push(make_pair(0, n));
    int u, v;
    double w, s;
    while (!q.empty()) {
        u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
		for (uint i = 0; i < fe[u].size(); i++) {
			v = fe[u][i].first, w = fe[u][i].second;
            if (d[v] > (s = d[u] + w))
                q.push(make_pair(-(d[v] = s), v));
        }
    }
}

int astar(int k) {
    q.push(make_pair(-d[1], 1));
    int u, v, ans = 0;
    double w, dis;
    while (!q.empty()) {
        u = q.top().second, dis = -q.top().first - d[u];
        q.pop();
        if (dis > W)
            return ans;
        ++cnt[u];
        if (u == n) {
            W -= dis, ++ans;
            continue;
        }
		for (uint i = 0; i < e[u].size(); i++) {
			v = e[u][i].first, w = e[u][i].second;
            if (cnt[v] < k)
                q.push(make_pair(-d[v] - dis - w, v));
        }
    }
    return ans;
}

template<typename T>
void read(T &x) {
    char ch;
    while (!isdigit(ch = getchar()));
    for (x = ch - '0'; isdigit(ch = getchar()); x = x * 10 + ch - '0');
}

int main() {
    //freopen("a.in", "r", stdin);
    int x, y;
    double z;
    read(n), read(m);
    scanf("%lf", &W);
    rep (i, 1, m) {
        read(x), read(y);
        scanf("%lf", &z);
		e[x].push_back(make_pair(y, z));
		fe[y].push_back(make_pair(x, z));
    }
    dij();
    printf("%d\n", astar(W / d[1]));
}
