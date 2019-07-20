#include <cstdio>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

inline void read(int &x)
{
    int b = x ^= x;
    while (*f < '0' && *f != '-')
        ++f;
    if (*f == '-')
        ++f, b = 1;
    while (*f >= '0')
        x = (x << 1) + (x << 3) + (*f ^ '0'), ++f;
    if (b)
        x = -x;
}

int main()
{
    int fd = fileno(stdin);
    struct stat sb;
    fstat(fd, &sb);
    register char *f = (char *)mmap(0, sb.st_size, 3, 2, fd, 0);

    long long ans = 0;
    unsigned N;
    register int x;
    read(N);
    int tmp = N & 3;
    N >>= 2;
    while (N--)
    {
        read(x);
        ans += x;
        read(x);
        ans += x;
        read(x);
        ans += x;
        read(x);
        ans += x;
    }
    while (tmp--)
    {
        read(x);
        ans += x;
    }
    printf("%lld\n", ans);
}