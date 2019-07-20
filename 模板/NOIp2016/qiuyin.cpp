#include <cstdio>
#include <vector>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
using namespace std;
typedef long long ll;

const int N = 7000005;
int s[2][N], a[N], he[5];
vector<ll> e[N], v[N];

#define read(x)       \
    x ^= x;           \
    while (*f < '0')  \
        ++f;          \
    while (*f >= '0') \
        x = (x << 1) + (x << 3) + (*f ^ '0'), ++f;

int main()
{
    int fd = fileno(stdin);
    struct stat sb;
    fstat(fd, &sb);
    register char *f = (char *)mmap(0, sb.st_size, 3, 2, fd, 0);

    int n, m, q, u, v, t, x;
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
    rep(i, 1, n)
    {
        read(x);
        a[i] = x;
    }
    he[1] = n;
    sort(a + 1, a + n + 1);
    double p = (double)u / v;
    rep (i, 1, m)
    {
        x = a[he[1]--];
        
    }
    return 0;
}