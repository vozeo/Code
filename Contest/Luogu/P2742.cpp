#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
int n, id, head, S[10005];

struct point
{
    double x, y;
    double operator*(point p) { return x * p.y - y * p.x; }
    point operator-(point p) { return (point){x - p.x, y - p.y}; }
    double dis() { return sqrt(x * x + y * y); }
} p[10005];

bool comp(point a, point b) { return (a - p[1]) * (b - p[1]) > 0; }

int main()
{
    id = 1;
    scanf("%d", &n);
    rep(i, 1, n) scanf("%lf%lf", &p[i].x, &p[i].y);
    rep(i, 1, n) if (p[i].x < p[id].y || (p[i].x == p[id].x && p[i].y < p[id].y))
        id = i;
    if (id != 1)
        std::swap(p[1], p[id]);
    std::sort(p + 2, p + n + 1, comp);
    S[++head] = 1;
    S[++head] = 2;
    rep(i, 3, n)
    {
        while (comp(p[S[i]], p[S[head]]) && head > 1)
            head--;
        S[++head] = i;
    }
    double ans = (p[S[head]] - p[S[1]]).dis();
    rep(i, 1, head - 1) ans += (p[S[i]] - p[S[i + 1]]).dis();
    rep(i, 1, head) printf("%.2f %.2f\n", p[S[i]].x, p[S[i]].y);
    printf("%.2f", ans);
    return 0;
}
