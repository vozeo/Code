#include <sys/mman.h>
#include <unistd.h>
#include <cctype>
#include <cstdio>
namespace IO
{
    char * in = static_cast <char *>(mmap(0,1 << 20,PROT_READ,MAP_PRIVATE,STDIN_FILENO,0)) - 1;
    inline void read(int & x)
    {
        x = 0;
        while (std::isspace(* ++ in));
        do
            x = 10 * x + (* in ^ 48);
        while (std::isdigit(* ++ in));
    }
    char pool[1 << 20],* out = pool - 1;
    inline void write(int x)
    {
        static char buf[10];
        char * idx = buf;
        do
            * idx ++ = x % 10 ^ 48;
        while (x /= 10);
        while (idx > buf)
            * ++ out = * -- idx;
    }
}
#define Max 50000
#include <cmath>
#include <algorithm>
#include <utility>
int C[Max + 1],count[Max + 1];
struct QUERY
{
    int ID,L,R,block;
    inline bool operator <(const QUERY & RHS) const
    {
        return block != RHS.block ? block < RHS.block : block & 1 ? R < RHS.R : R > RHS.R;
    }
}query[Max];
using PII = std::pair <int,int>;
PII out[Max];
int main()
{
    int N,M;
    IO::read(N),IO::read(M);
    for (int i = 1;i <= N;++ i)
        IO::read(C[i]);
    int size = N / sqrt((M << 1) / 3);
    for (int i = 0;i < M;++ i)
    {
        QUERY & query = ::query[i];
        query.ID = i,IO::read(query.L),IO::read(query.R),query.block = (query.L - 1) / size;
    }
    std::sort(query,query + M);
    int L = query[0].L,R = L - 1;
    for (int i = 0;i < M;++ i)
    {
        int curL = query[i].L,curR = query[i].R;
        PII & ans = out[query[i].ID];
        if (__builtin_expect(curL != curR,1))
        {
            static int sum;
            while (L > curL)
                sum += count[C[-- L]] ++;
            while (R < curR)
                sum += count[C[++ R]] ++;
            while (L < curL)
                sum -= -- count[C[L ++]];
            while (R > curR)
                sum -= -- count[C[R --]];
            ans.first = sum,ans.second = (R - L) & 1 ? (R - L + 1 >> 1) * (R - L) : (R - L + 1) * (R - L >> 1);
            int GCD = std::__gcd(ans.first,ans.second);
            ans.first /= GCD,ans.second /= GCD;
        }
        else
            ans.first = 0,ans.second = 1;
    }
    for (int i = 0;i < M;++ i)
        IO::write(out[i].first),* ++ IO::out = '/',IO::write(out[i].second),* ++ IO::out = '\n';
    std::fwrite(IO::pool,1,IO::out - IO::pool + 1,stdout);
}
